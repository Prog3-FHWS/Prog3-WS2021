import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { BoardComponent } from '../lib/feature/board/board.component';
import { ColumnComponent } from '../lib/feature/column/column.component';
import { ItemComponent } from '../lib/feature/item/item.component';
import { createButtonComponent } from '../lib/ui/createButton/createButton.component';
import { ToolbarComponent } from '../lib/ui/toolbar/toolbar.component';
import { TrashComponent } from '../lib/ui/trash/trash.component';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';

@NgModule({
  declarations: [
    AppComponent,
    ToolbarComponent,
    ColumnComponent,
    ItemComponent,
    createButtonComponent,
    BoardComponent,
    TrashComponent,
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    BrowserModule,
    BrowserAnimationsModule,
  ],
  providers: [],
  bootstrap: [AppComponent],
})
export class AppModule {}
