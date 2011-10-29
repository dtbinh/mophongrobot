class MayaCamera
{
public:
	float	 m_fLastX;
	float	 m_fLastY;
	float	 m_fPosX;
	float	 m_fPosY;
	float	 m_fZoom;
	float	 m_fRotX;
	float	 m_fRotY;

	MayaCamera()
	{
		m_fPosX = 0.0f;    // X position of model in camera view
		m_fPosY = 0.0f;    // Y position of model in camera view
		m_fZoom = 10.0f;   // Zoom on model in camera view
		m_fRotX = 0.0f;    // Rotation on model in camera view
		m_fRotY = 0.0f;    // Rotation on model in camera view
	}

	void UpdateView()
	{
		glTranslatef(0.0f, 0.0f, -m_fZoom);
		glTranslatef(m_fPosX, m_fPosY, 0.0f);
		glRotatef(m_fRotX, 1.0f, 0.0f, 0.0f);
		glRotatef(m_fRotY, 0.0f, 1.0f, 0.0f);
	}
	void UpdateOnMouseMove(WPARAM wParam, LPARAM lParam)
	{
		int xPos = GET_X_LPARAM(lParam); 
		int yPos = GET_Y_LPARAM(lParam); 

		int diffX = (int)(xPos - m_fLastX);
		int diffY = (int)(yPos - m_fLastY);
		m_fLastX  = (float)xPos;
		m_fLastY  = (float)yPos;

		int nFlags = wParam;

		// Left mouse button
		if (nFlags & MK_LBUTTON)
		{
			m_fRotX += (float)0.5f * diffY;

			if ((m_fRotX > 360.0f) || (m_fRotX < -360.0f))
			{
				m_fRotX = 0.0f;
			}

			m_fRotY += (float)0.5f * diffX;

			if ((m_fRotY > 360.0f) || (m_fRotY < -360.0f))
			{
				m_fRotY = 0.0f;
			}
		}

		// Right mouse button
		else if (nFlags & MK_RBUTTON)
		{
			m_fZoom -= (float)0.1f * diffY;
		}

		// Middle mouse button
		else if (nFlags & MK_MBUTTON)
		{
			m_fPosX += (float)0.05f * diffX;
			m_fPosY -= (float)0.05f * diffY;
		}
	}
};