
void DrawAxes(float axisSize = 3.0f, float lineWidth = 2.0f)
{
	const GLfloat xAxizColor[4] = {1, 0, 0, 1};
	const GLfloat yAxizColor[4] = {0, 1, 0, 1};
	const GLfloat zAxizColor[4] = {0, 0, 1, 1};

		//	Set up some nice attributes for drawing the grid.
	glPushAttrib(GL_LINE_BIT | GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(lineWidth);
	//	Create the axies.
	glBegin(GL_LINES);
	{
		glColor4fv(xAxizColor);
		glVertex3f(0, 0, 0);
		glVertex3f(axisSize, 0, 0);
		glColor4fv(yAxizColor);
		glVertex3f(0, 0, 0);
		glVertex3f(0, axisSize, 0);
		glColor4fv(zAxizColor);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, axisSize);
	}
	glEnd();

	glPopAttrib();
}
