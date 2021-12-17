import {
  AfterViewInit,
  Component,
  ElementRef,
  EventEmitter,
  Input,
  Output,
  ViewChild,
} from '@angular/core';
import { Item } from '../../data-access/item';

@Component({
  selector: 'item',
  templateUrl: './item.component.html',
  styleUrls: ['./item.component.scss'],
})
export class ItemComponent implements AfterViewInit {
  @Input() itemObject: Item;
  @Input() selectedOnCreate: boolean;
  @Input() color: string = '#29b9e6';
  @Output() clickDeleteEvent = new EventEmitter<number>();

  @ViewChild('myInput') myInput: ElementRef;

  showTrash: boolean = false;
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
  }

  clickEvent(): void {
    this.clickDeleteEvent.emit(this.itemObject.getID());
  }

  editValue(event: any): void {
    this.itemObject.setValue(event.target.value);
  }
}
