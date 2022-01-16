import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Board, Column, Item } from '../models';

@Injectable({
  providedIn: 'root',
})
export class BackendService {
  readonly url: string = 'http://localhost:4200';

  constructor(private httpClient: HttpClient) {}

  loadBoard(): Observable<Board> {
    return this.httpClient.get<Board>(this.url + '/api/board');
  }

  createColumn(column: Column): Observable<Column> {
    let columnPayload = {
      ...column,
    };

    return this.httpClient.post<Column>(
      this.url + '/api/board/columns',
      columnPayload
    );
  }

  deleteColumn(columnId: number): Observable<void> {
    return this.httpClient.delete<void>(
      this.url + '/api/board/columns/' + columnId
    );
  }

  updateColumn(column: Partial<Column>): Observable<Column> {
    let columnPayload = {
      ...column,
    };

    return this.httpClient.put<Column>(
      this.url + '/api/board/columns/' + column.id,
      columnPayload
    );
  }

  createItem(columnId: number, item: Partial<Item>): Observable<Item> {
    let itemPayload = {
      ...item,
    };

    return this.httpClient.post<Item>(
      this.url + '/api/board/columns/' + columnId + '/items',
      itemPayload
    );
  }

  deleteItem(columnId: number, itemId: number): Observable<void> {
    return this.httpClient.delete<void>(
      this.url + '/api/board/columns/' + columnId + '/items/' + itemId
    );
  }

  updateItem(columnId: number, item: Partial<Item>): Observable<Item> {
    let itemPayload = {
      ...item,
    };

    return this.httpClient.put<Item>(
      this.url + '/api/board/columns/' + columnId + '/items/' + item.id,
      itemPayload
    );
  }
}
