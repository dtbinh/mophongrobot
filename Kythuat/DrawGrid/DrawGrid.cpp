
void DrawGrid(int gridSize = 10, float gridElev=0, float lineWidth = 0.5f)
{
	//	Set up some nice attributes for drawing the grid.
	glPushAttrib(GL_LINE_BIT | GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(lineWidth);

	//	Create the grid.

    glBegin(GL_LINES);
	{
		for (int i = -gridSize; i <= gridSize; i++)
		{
			glColor4f(0.2f, 0.2f, 0.2f, 0.8f);
			glVertex3f((float)i, 0, -(float)gridSize);
			glVertex3f((float)i, 0, +(float)gridSize);
			glVertex3f(-(float)gridSize, 0, (float)i);
			glVertex3f(+(float)gridSize, 0, (float)i);
		}
	}
	glEnd();

	glPopAttrib();
}
