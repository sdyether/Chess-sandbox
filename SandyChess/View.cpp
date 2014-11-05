#include "View.h"
#include "Canvas.h"
#include "Model.h"

void View::Paint(Canvas & canvas, Model & model) {
	canvas.Text(12, 1, model.GetText(), model.GetLen());
	canvas.Line(10,0,10, y);
}