import { Component, EventEmitter, Input, Output } from '@angular/core';

@Component({
  selector: 'createButton',
  templateUrl: './createButton.component.html',
  styleUrls: ['./createButton.component.scss'],
})
export class createButtonComponent {
  @Input() backgroundColor: string = '#d6d6d6';
  @Input() borderRadius: string = '10px';
  @Output() newClickEvent = new EventEmitter<void>();

  clickEvent(): void {
    this.newClickEvent.emit();
  }
}
