
import pytest
import requests

BASE_URI = 'http://0.0.0.0:8080/api/'


@pytest.fixture(autouse=True)
def check_service():
    try:
        requests.get(BASE_URI + 'board')
    except (requests.exceptions.ConnectionError, requests.exceptions.Timeout):
        pytest.fail("service not running")

def get_column_by_id(column_id, db_conn):
  cursor = db_conn.cursor()

  cursor.execute("Select id, name, position from column where column.id=?", (column_id,))
  fetched_column = cursor.fetchone()

  if (fetched_column):
    result = {'id': fetched_column[0], 'name': fetched_column[1], 'position': fetched_column[2]}
  else:
    result = None
  return result

def get_item_by_id(item_id, db_conn):
  cursor = db_conn.cursor()

  cursor.execute("select id, title, position, date, column_id from item where item.id=?", (item_id,))
  fetched_item = cursor.fetchone()

  if (fetched_item):
    column_id = fetched_item[4]
    result = (column_id, {'id': fetched_item[0], 'title': fetched_item[1], 'position': fetched_item[2], 'timestamp': fetched_item[3]})
  else:
    result = (None, None)

  return result

def test_board_get(db_with_data):
  resp = requests.get(BASE_URI + 'board')
  assert resp.status_code == 200

  resp_body = resp.json()
  assert resp_body['title'] == "Kanban Board"

  columns = resp_body["columns"]
  assert len(columns) == 3

  items_first_column = columns[0]['items']
  items_second_column = columns[1]['items']
  items_third_column = columns[2]['items']

  assert len(items_first_column) == 1
  assert len(items_second_column) == 2
  assert len(items_third_column) == 0

def test_columns_get_all(db_with_data):
  resp = requests.get(BASE_URI + 'board/columns')
  assert resp.status_code == 200

  resp_body = resp.json()
  assert len(resp_body) == 3

  items_first_column = resp_body[0]['items']
  items_second_column = resp_body[1]['items']
  items_third_column = resp_body[2]['items']

  assert len(items_first_column) == 1
  assert len(items_second_column) == 2
  assert len(items_third_column) == 0

def test_columns_post(db_with_data):
  payload = {'name': "test_column_post", 'position': 4}
  resp = requests.post(BASE_URI + 'board/columns', json=payload)

  assert resp.status_code == 201

  resp_body = resp.json()
  posted_column_id = resp_body.get('id')

  posted_colum = get_column_by_id(posted_column_id, db_with_data)

  resp_body.pop('items', None)
  assert posted_colum == resp_body


def test_columns_post_wrong(db_with_data):
  payload = {'name': "columns_post_right", 'position': 5}
  resp = requests.post(BASE_URI + 'board/columns', json=payload)
  assert any(resp.json()) == True

  payload = {'name': "columns_post_wrong", 'position': 1}
  resp = requests.post(BASE_URI + 'board/columns', json=payload)
  assert any(resp.json()) == False


def test_columns_get(db_with_data):
  COLUMN_ID = 2
  resp = requests.get(BASE_URI + 'board/columns/' + str(COLUMN_ID))
  assert resp.status_code == 200

  resp_body = resp.json()
  assert resp_body.get('id') == COLUMN_ID
  assert resp_body.get('name') == 'running'
  assert resp_body.get('position') == 2
  assert len(resp_body.get('items')) == 2

def test_columns_get_wrong(db_with_data):
  WRONG_COLUMN_ID = 99
  resp = requests.get(BASE_URI + 'board/columns/' + str(WRONG_COLUMN_ID))
  assert any(resp.json()) == False

def test_columns_put_response(db_with_data):
  COLUMN_ID = 2
  payload = {'name': "test_column_put", 'position': 5}
  resp = requests.put(BASE_URI + 'board/columns/' + str(COLUMN_ID), json=payload)
  assert resp.status_code == 200
  resp_body = resp.json()
  assert resp_body.get('id') == COLUMN_ID
  assert resp_body.get('name') == 'test_column_put'
  assert resp_body.get('position') == 5
  assert len(resp_body.get('items')) == 2

def test_columns_put_database(db_with_data):
  COLUMN_ID = 2
  payload = {'name': "test_column_put", 'position': 5}
  requests.put(BASE_URI + 'board/columns/' + str(COLUMN_ID), json=payload)

  changed_colum = get_column_by_id(COLUMN_ID, db_with_data)

  assert changed_colum.get('id') == COLUMN_ID
  assert changed_colum.get('name') == 'test_column_put'
  assert changed_colum.get('position') == 5


def test_columns_put_wrong(db_with_data):
  RIGHT_COLUMN_ID = 2
  WRONG_COLUMN_ID = 99
  payload = {'name': "test_column_put_wrong", 'position': 3}
  resp = requests.put(BASE_URI + 'board/columns/' + str(RIGHT_COLUMN_ID), json=payload)
  resp_body = resp.json()
  if len(resp_body) > 0:
    assert resp_body.get('id') == RIGHT_COLUMN_ID
    assert resp_body.get('name') != 'test_column_put_wrong'
    assert resp_body.get('position') != 3

  resp = requests.put(BASE_URI + 'board/columns/' + str(WRONG_COLUMN_ID), json=payload)
  assert any(resp.json()) == False

def test_columns_delete(db_with_data):
  COLUMN_ID = 2
  column_to_delete = get_column_by_id(COLUMN_ID, db_with_data)
  assert column_to_delete is not None

  resp = requests.delete(BASE_URI + 'board/columns/' + str(COLUMN_ID))
  assert resp.status_code == 200
  deleted_column = get_column_by_id(COLUMN_ID, db_with_data)
  assert deleted_column is None

def test_items_get_all(db_with_data):
  resp = requests.get(BASE_URI + 'board/columns/1/items')
  assert resp.status_code == 200

  resp_body = resp.json()
  assert len(resp_body) == 1

  resp = requests.get(BASE_URI + 'board/columns/2/items')
  assert resp.status_code == 200

  resp_body = resp.json()
  assert len(resp_body) == 2

  assert resp_body[0].get('id') == 2
  assert resp_body[1].get('id') == 3

  assert resp_body[0].get('title') == 'running task 1'
  assert resp_body[1].get('title') == 'running task 2'

def test_items_get_empty_column(db_with_data):
  resp = requests.get(BASE_URI + 'board/columns/3/items')
  assert resp.status_code == 200
  assert any(resp.json()) == False

def test_items_post(db_with_data):
  TEST_COLUMN_ID = 2
  payload = {'title': "test_item_post", 'position': 3}
  resp = requests.post(BASE_URI + 'board/columns/' + str(TEST_COLUMN_ID) + '/items', json=payload)

  assert resp.status_code == 201

  resp_body = resp.json()
  posted_item_id = resp_body.get('id')

  (column_id, posted_item) = get_item_by_id(posted_item_id, db_with_data)

  assert column_id == TEST_COLUMN_ID
  assert posted_item == resp_body

def test_items_post_wrong(db_with_data):
  TEST_COLUMN_ID = 2
  payload = {'title': "test_item_post_right", 'position': 3}
  resp = requests.post(BASE_URI + 'board/columns/' + str(TEST_COLUMN_ID) + '/items', json=payload)
  assert any(resp.json()) == True

  payload = {'title': "test_item_post_wrong", 'position': 1}
  resp = requests.post(BASE_URI + 'board/columns/' + str(TEST_COLUMN_ID) + '/items', json=payload)
  assert any(resp.json()) == False

def test_items_get(db_with_data):
  ITEM_ID = 2
  resp = requests.get(BASE_URI + 'board/columns/2/items/' + str(ITEM_ID))
  assert resp.status_code == 200

  resp_body = resp.json()

  assert resp_body.get('id') == ITEM_ID
  assert resp_body.get('title') == 'running task 1'
  assert resp_body.get('position') == 1
  assert len(resp_body.get('timestamp')) > 0

def test_items_get_wrong(db_with_data):
  WRONG_ITEM_ID = 99
  resp = requests.get(BASE_URI + 'board/columns/2/items/' + str(WRONG_ITEM_ID))
  assert any(resp.json()) == False

def test_items_put_response(db_with_data):
  ITEM_ID = 2
  payload = {'title': "test_item_put", 'position': 3}
  resp = requests.put(BASE_URI + 'board/columns/2/items/' + str(ITEM_ID), json=payload)
  assert resp.status_code == 200

  resp_body = resp.json()
  assert resp_body.get('id') == ITEM_ID
  assert resp_body.get('title') == 'test_item_put'
  assert resp_body.get('position') == 3
  assert len(resp_body.get('timestamp')) > 0

def test_items_put_database(db_with_data):
  ITEM_ID = 2
  payload = {'title': "test_item_put", 'position': 3}
  requests.put(BASE_URI + 'board/columns/2/items/' + str(ITEM_ID), json=payload)

  (column_id, changed_item) = get_item_by_id(ITEM_ID, db_with_data)
  assert column_id == 2

  assert changed_item.get('id') == ITEM_ID
  assert changed_item.get('title') == 'test_item_put'
  assert changed_item.get('position') == 3

def test_items_put_wrong(db_with_data):
  RIGHT_ITEM_ID = 2
  WRONG_ITEM_ID = 99
  payload = {'title': "test_item_put_wrong", 'position': 2}
  resp = requests.put(BASE_URI + 'board/columns/2/items/' + str(RIGHT_ITEM_ID), json=payload)
  resp_body = resp.json()
  if len(resp_body) > 0:
    assert resp_body.get('id') == RIGHT_ITEM_ID
    assert resp_body.get('name') != 'test_item_put_wrong'
    assert resp_body.get('position') != 2

  resp = requests.put(BASE_URI + 'board/columns/2/items/' + str(WRONG_ITEM_ID), json=payload)
  assert any(resp.json()) == False


def test_items_delete(db_with_data):
  ITEM_ID = 2
  column_id, item_to_delete = get_item_by_id(ITEM_ID, db_with_data)
  assert item_to_delete is not None
  assert column_id is not None

  resp = requests.delete(BASE_URI + 'board/columns/2/items/' + str(ITEM_ID))
  assert resp.status_code == 200
  column_id, deleted_item = get_item_by_id(ITEM_ID, db_with_data)
  assert column_id is None
  assert deleted_item is None
