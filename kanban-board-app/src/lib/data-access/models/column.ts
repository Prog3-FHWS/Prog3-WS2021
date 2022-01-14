import { Item } from './item';

export class Column {
  id?: number;
  name: string;
  position: number;
  items: Item[];
}
