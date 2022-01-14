import { Component, Input, OnInit } from '@angular/core';
import { Board, Column } from 'src/lib/data-access/models';
import { BackendService } from 'src/lib/data-access/services/backend.service';

@Component({
  selector: 'board',
  templateUrl: './board.component.html',
  styleUrls: ['./board.component.scss'],
})
export class BoardComponent implements OnInit {
  @Input() title: string;
  @Input() color: string = '#29b9e6';

  board?: Board;
  newColumnIndex?: number;

  constructor(private backendService: BackendService) {}

  ngOnInit(): void {
    this.backendService.loadBoard().subscribe((board) => (this.board = board));
  }

  createNewColumn(): void {
    let newColumn: Column = { name: '', position: 0, items: [] };
    this.newColumnIndex = this.board.columns.push(newColumn) - 1;
    newColumn.position =
      this.newColumnIndex === 0
        ? 1
        : this.board.columns[this.newColumnIndex - 1].position + 1;

    this.backendService.createColumn(newColumn).subscribe((column) => {
      newColumn.id = column.id;
      newColumn.position = column.position;
    });
  }

  deleteColumn(columnId: number): void {
    const index = this.board.columns.findIndex(
      (column) => column.id === columnId
    );
    this.board.columns.splice(index, 1);

    this.backendService.deleteColumn(columnId).subscribe();
  }
}
