 #!/bin/bash

#echo "the current directory is : $(pwd)"

scriptLocation=$(readlink -f "$0")
scriptLocationDir=$(dirname "$scriptLocation")
logfile=$scriptLocationDir/testAll.log
assignmentDir=$scriptLocationDir/assignments
venvDir=$scriptLocationDir/venv
pytestScript=$scriptLocationDir/test_service.py

#echo $pytestScript
#echo $scriptLocationDir
#echo $logfile
#echo $assignmentDir
#echo $venvDir

enterAssignment() {
    echo "" | tee -a $logfile
    echo "start with assignment $1" | tee -a $logfile
    cd "$1/kanban-board-service"
}

leaveAssignment() {

    # comment in for clean build every time ;)
    # if [[ -d "build" ]]; then
    #     echo "remove build directory"
    #     rm -rf ./build
    # fi

    if [[ -d "../data" ]]; then
        echo "remove database"
        rm -rf ../data
    fi

    echo "finished with assignment $1" | tee -a $logfile
    echo "" | tee -a $logfile
    echo "------------------------------------------" | tee -a $logfile
    echo "------------------------------------------"
    cd ../..
}

echo "starting testAll.sh" | tee $logfile
echo "===================" | tee -a $logfile

if [[ -d $venvDir ]]; then
    echo "$venvDir available --> activating python venv" | tee -a $logfile
    echo "------------------------------------------" | tee -a $logfile
    echo "------------------------------------------" | tee -a $logfile
    source "./venv/bin/activate"
fi

cd $assignmentDir

for d in */ ; do

    if [[ ! -d "$d/kanban-board-service" ]]; then
        echo "ERROR: skipping assignment: $d --> no service folder available" | tee -a $logfile
        continue
    fi

    enterAssignment $d
    
    # cmake -DCMAKE_BUILD_TYPE:STRING=Debug -S . -B ./build > /dev/null
    cmake -DCMAKE_BUILD_TYPE:STRING=Debug -S . -B ./build 2>>$logfile

    cmake --build ./build --config Debug --target all -- -j 4 2>>$logfile
    result=$?
    if [ $result -ne 0 ]; then
        echo "" | tee -a $logfile
        echo "ERROR: building assignment $d with result: $result" | tee -a $logfile
        leaveAssignment $d
        continue
    fi

    # ./build/Service > /dev/null 2>&1 &
    ./build/Service > /dev/null 2>"service.log" &
    servicePid=$!
    sleep 1

    pytest -s -v -rs $pytestScript | tee "pytest.log"

    sleep 1
    kill $servicePid

    leaveAssignment $d

done

if [[ -d $venvDir ]]; then
    echo "leaving python venv ..."
    deactivate
fi
