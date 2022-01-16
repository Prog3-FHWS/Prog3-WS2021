import { Item } from './item';

export interface Column {
  id?: number;
  name: string;
  position: number;
  items: Item[];
}
