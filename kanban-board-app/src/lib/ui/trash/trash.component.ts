import { Component, EventEmitter, Output } from '@angular/core';

@Component({
  selector: 'trash',
  templateUrl: './trash.component.html',
  styleUrls: ['./trash.component.scss'],
})
export class TrashComponent {
  @Output() newClickEvent = new EventEmitter<any>();

  clickEvent(): void {
    this.newClickEvent.emit();
  }
}
