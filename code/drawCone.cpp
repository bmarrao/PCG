void drawCone(float radius, float height, int slices,int stacks	) 
{
    int i = 0;
    float j;
    float x;
    float ang = 2*M_PI / slices;
	float dify = height /stacks ;
	float difr = radius / stacks ;
	point ant ;
	point act ;	
	point aux1;
	point aux2;
	float radius1;
    for (;i < slices; )
    {
        x = ang * i;
        i++;
        j = ang * i;
		//ant.x
		ant.x = radius*sin(x);
		//ant.z
		ant.y = 0;
		//z1
		ant.z = radius * cos(x);
		//act.x
		act.x = radius*sin(j);
		//y2
		act.y = 0;
		//z2
		act.z = radius * cos(j);
        glBegin(GL_TRIANGLES);

		//Base Baixo
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(ant.x, 0.0f, ant.z);
        glVertex3f(act.x, 0.0f,act.z);
        glVertex3f(0.0f, 0.0f, 0.0f);     

		radius1 = (radius -  difr );
		aux1.y = 0;
		aux2.y = 0;

		for (int l = 1; l < stacks; l++)
		{
			//FALTA DESCOBRIR O Q PRECISO APLICAR AQUI
			radius1 = (radius1 -  difr );
			aux1.x = radius1 * sin(x);
			aux1.y = aux1.y + dify;
			aux1.z = radius1 * cos(x);
			aux2.x = radius1*sin(j);
			aux2.y = aux2.y + dify;
			aux2.z = radius1 * cos(j);
			
			glColor3f(0.5, 1.0, 0.0);

			glVertex3f(ant.x, ant.y, ant.z);
			glVertex3f(act.x, act.y, act.z);
			glVertex3f(aux2.x, aux2.y, aux2.z); 

			glColor3f(0.0, 1.0, 0.5);


			glVertex3f(aux2.x, aux2.y, aux2.z);
			glVertex3f(aux1.x, aux1.y, aux1.z);
			glVertex3f(ant.x, ant.y, ant.z); 

			//ACT E ANT VIRAM AUX1 e AUX2
			ant = aux1;
			act = aux2;
			
	
		}

		//ultimo triang
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(ant.x, 0.0f, ant.z);
        glVertex3f(act.x, 0.0f, act.z);
        glVertex3f(0.0f, height, 0.0f); 
		glEnd();
	
	
    }
// put code to draw cylinder in here

}