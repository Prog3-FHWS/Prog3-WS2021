import sqlite3
from datetime import datetime
from pathlib import Path

import pytest

DATABASE_LOCATION = 'data/kanban-board.db'


def pytest_terminal_summary(terminalreporter, exitstatus, config):
    print('\n')
    tests_passed = 0
    tests_failed = 0

    try:
        tests_passed = len(terminalreporter.stats['passed'])
    except KeyError:
        return

    try:
        tests_failed = len(terminalreporter.stats['failed'])
    except KeyError:
        pass

    assignmentPoints = (tests_passed / (tests_passed + tests_failed)) * 100
    assignmentPoints = round(assignmentPoints, 2)
    print('number of passed tests: ' + str(tests_passed))
    print('number of failed tests: ' + str(tests_failed))
    print('=========================================')
    print('points reached in assignment: ' + str(assignmentPoints) + ' of 100')
    print('=========================================')


@pytest.fixture(scope="module")
def db_connection():

    if Path(DATABASE_LOCATION).is_file():
        conn = sqlite3.connect(DATABASE_LOCATION)
        yield conn
        conn.close()
    else:
        pytest.fail("SQLite Database not found")


@pytest.fixture
def db_with_data(db_connection):
    clear_database(db_connection)
    create_dummy_data(db_connection)
    yield db_connection
    clear_database(db_connection)


def clear_database(db_conn):
    cursor = db_conn.cursor()
    cursor.execute("DELETE FROM column")
    cursor.execute("DELETE FROM item")
    db_conn.commit()


def create_dummy_data(db_conn):
    cursor = db_conn.cursor()

    columns = [(1, "prepare", 1),
               (2, "running", 2),
               (3, "finished", 3)]
    items = [(1, "in plan", datetime.now(), 1, 1),
             (2, "running task 1", datetime.now(), 1, 2),
             (3, "running task 2", datetime.now(), 2, 2)]

    cursor.executemany("INSERT INTO column VALUES(?, ?, ?)", columns)
    cursor.executemany("INSERT INTO item VALUES (?, ?, ?, ?, ?)", items)

    db_conn.commit()
