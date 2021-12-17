export class Item {
  private id: number;
  private value: string;

  constructor(id: number, value: string) {
    this.id = id;
    this.value = value;
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
}
