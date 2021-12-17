import { Component, Input, OnInit } from '@angular/core';
import { Board } from '../../data-access/board';
import { Column } from '../../data-access/column';

@Component({
  selector: 'board',
  templateUrl: './board.component.html',
  styleUrls: ['./board.component.scss'],
})
export class BoardComponent implements OnInit {
  @Input() title: string;
  @Input() color: string = '#29b9e6';
  boardObject: Board;
  selected: Column;

  ngOnInit(): void {
    this.boardObject = new Board(this.title);
  }

  createNewColumn(input: any): void {
    this.selected = this.boardObject.addColumn();
  }

  deleteColumn(id: number): void {
    this.boardObject.removeColumn(id);
  }
}
