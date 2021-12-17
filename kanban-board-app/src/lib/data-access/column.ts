import { Item } from './item';

export class Column {
  private id: number;
  private value: string;
  private items: Item[] = [];

  static itemCounter: number = 0;

  constructor(id: number, value: string) {
    this.id = id;
    this.value = value;
  }

  addItem(): Item {
    let item: Item = new Item(Column.itemCounter++, '');
    this.items.push(item);
    return item;
  }

  removeItem(id: number): void {
    let i: number = this.getItemPosition(id);
    if (id != -1) this.items.splice(i, 1);
  }

  getItemPosition(itemID: number): number {
    for (var i = 0; i < this.items.length; i++) {
      if (this.items[i].getID() == itemID) {
        return i;
      }
    }
    return -1;
  }

  setValue(newValue: string): void {
    this.value = newValue;
  }

  getValue(): string {
    return this.value;
  }

  getID(): number {
    return this.id;
  }

  getItems(): Item[] {
    return this.items;
  }
}
