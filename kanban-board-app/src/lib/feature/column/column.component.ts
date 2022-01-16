import {
  AfterViewInit,
  Component,
  ElementRef,
  EventEmitter,
  Input,
  Output,
  ViewChild,
} from '@angular/core';
import { Column, Item } from 'src/lib/data-access/models';
import { BackendService } from 'src/lib/data-access/services/backend.service';

@Component({
  selector: 'column',
  templateUrl: './column.component.html',
  styleUrls: ['./column.component.scss'],
})
export class ColumnComponent implements AfterViewInit {
  @Input() column: Column;
  @Input() selectedOnCreate: boolean;
  @Input() color: string = '#29b9e6';
  @Output() delete = new EventEmitter<number>();

  @ViewChild('columnNameInput') columnNameInput: ElementRef;

  showTrash: boolean = false;
  newItemIndex: number;
  elementRef: ElementRef;

  constructor(private backendService: BackendService) {}

  ngAfterViewInit(): void {
    if (this.selectedOnCreate) {
      this.columnNameInput.nativeElement.focus();
    }
  }

  onMouseEnter(): void {
    this.showTrash = true;
  }

  onMouseLeave(): void {
    this.showTrash = false;
  }

  onDeleteColumn(): void {
    this.delete.emit(this.column.id);
  }

  onCreateNewItem(): void {
    let newItem: Item = { title: '', position: 0 };
    this.newItemIndex = this.column.items.push(newItem) - 1;
    newItem.position =
      this.newItemIndex === 0
        ? 1
        : this.column.items[this.newItemIndex - 1].position + 1;

    this.backendService
      .createItem(this.column.id, newItem)
      .subscribe((item) => {
        newItem.id = item.id;
        newItem.position = item.position;
      });
  }

  onItemDelete(itemId: number): void {
    const index = this.column.items.findIndex((item) => item.id === itemId);
    this.column.items.splice(index, 1);

    this.backendService.deleteItem(this.column.id, itemId).subscribe();
  }

  onItemChange(item: Item): void {
    this.backendService.updateItem(this.column.id, item).subscribe();
  }

  onNameChange(event: KeyboardEvent): void {
    this.column.name = (event.target as HTMLInputElement).value;
    this.backendService.updateColumn(this.column).subscribe();
  }
}
