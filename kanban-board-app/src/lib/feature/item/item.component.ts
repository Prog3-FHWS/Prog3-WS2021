import {
  AfterViewInit,
  Component,
  ElementRef,
  EventEmitter,
  Input,
  Output,
  ViewChild,
} from '@angular/core';
import { Item } from 'src/lib/data-access/models';
import { BackendService } from 'src/lib/data-access/services/backend.service';
@Component({
  selector: 'item',
  templateUrl: './item.component.html',
  styleUrls: ['./item.component.scss'],
})
export class ItemComponent implements AfterViewInit {
  @Input() item: Item;
  @Input() selectedOnCreate: boolean;
  @Input() color: string = '#29b9e6';

  @Output() itemDelete = new EventEmitter<number>();
  @Output() itemChange = new EventEmitter<Item>();

  @ViewChild('itemTitleInput') itemTitleInput: ElementRef;

  showTrash: boolean = false;
  elementRef: ElementRef;

  constructor(private backendService: BackendService) {}

  ngAfterViewInit(): void {
    if (this.selectedOnCreate) {
      this.itemTitleInput.nativeElement.focus();
    }
  }

  onMouseEnter(): void {
    this.showTrash = true;
  }

  onMouseLeave(): void {
    this.showTrash = false;
  }

  onDelete(): void {
    this.itemDelete.emit(this.item.id);
  }

  onTitleChange(event: KeyboardEvent): void {
    this.item.title = (event.target as HTMLInputElement).value;
    this.itemChange.emit(this.item);
  }
}
