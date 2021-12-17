import {
  AfterViewInit,
  Component,
  ElementRef,
  EventEmitter,
  Input,
  Output,
  ViewChild,
} from '@angular/core';
import { Column } from '../../data-access/column';
import { Item } from '../../data-access/item';

@Component({
  selector: 'column',
  templateUrl: './column.component.html',
  styleUrls: ['./column.component.scss'],
})
export class ColumnComponent implements AfterViewInit {
  @Input() columnObject: Column;
  @Input() selectedOnCreate: boolean;
  @Input() color: string = '#29b9e6';
  @Output() clickDeleteEvent = new EventEmitter<number>();

  @ViewChild('myInput') myInput: ElementRef;

  showTrash: boolean = false;
  selectedObject: Item;
  elementRef: ElementRef;

  ngAfterViewInit(): void {
    if (this.selectedOnCreate) {
      this.myInput.nativeElement.focus();
    }
  }

  hoverEvent(): void {
    this.showTrash = true;
  }

  mouseOutEvent(): void {
    this.showTrash = false;
    console.log('out');
  }

  clickEvent(): void {
    this.clickDeleteEvent.emit(this.columnObject.getID());
  }

  createNewItem(input: any): void {
    this.selectedObject = this.columnObject.addItem();
  }

  deleteItem(id: number): void {
    this.columnObject.removeItem(id);
  }

  editValue(event: any): void {
    this.columnObject.setValue(event.target.value);
  }
}
