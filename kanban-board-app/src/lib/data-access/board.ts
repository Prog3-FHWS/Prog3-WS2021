import { Column } from './column';

export class Board {
  private title: string;
  private columns: Column[] = [];

  constructor(title: string) {
    this.title = title;
  }

  addColumn(): Column {
    let column: Column = new Column(this.columns.length, '');
    this.columns.push(column);
    return column;
  }

  removeColumn(id: number): void {
    let i: number = this.getColumnPosition(id);
    if (id != -1) this.columns.splice(i, 1);
  }

  getColumnPosition(columnID: number): number {
    for (var i = 0; i < this.columns.length; i++) {
      if (this.columns[i].getID() == columnID) {
        return i;
      }
    }
    return -1;
  }

  getTitle(): string {
    return this.title;
  }

  getColumns(): Column[] {
    return this.columns;
  }
}
