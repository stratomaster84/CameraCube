// ImageLoad.c
// OpenGL SuperBible
// Demonstrates loading a color image
// Program by Richard S. Wright Jr.

#include <GL\OpenGLSB.h>	// System and OpenGL Stuff
#include <GL\GLTools.h>	// OpenGL toolkit

#include "AVI_text.h"
#include <math.h>
#include <float.h>


long _H=1024,_W=768;
_AVI_texture _tex[5];
static GLfloat theta[] = {0,0};
static GLfloat theta2[] = {0,0};

#define MINZPOS  3
#define MAXZPOS  30
static GLfloat zPos = 18.0f;

GLuint textures[6];
int _gran_num = 0;
bool camera_state = false;

GLTVector3 vCorners[8] =                {{-1.0f,-1.0f,1.0f},
                                        { -1.0f,1.0f,1.0f},
                                        {1.0f,1.0f,1.0f},
                                        {1.0f,-1.0f,1.0f},
                                        {-1.0f,-1.0f,-1.0f},
                                        { -1.0f,1.0f,-1.0f},
                                        {1.0f,1.0f,-1.0f},
                                        {1.0f,-1.0f,-1.0f}};

//////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering
// context.
void SetupRC(const char* filename){
        _control87(MCW_EM, MCW_EM);
        AVIFileInit();
        for(int i=0;i<5;i++){
                if(!_tex[i].AVI_Init("gl256.avi"))
                        exit(0);
                _tex[i].Set_Format(i);    // плохо
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

        glFrontFace(GL_CCW);
        glEnable(GL_CULL_FACE);

        glReadBuffer(GL_BACK);

        glGenTextures(6,textures);

        for(int i=0;i<6;i++){
                glBindTexture(GL_TEXTURE_2D,textures[i]);

                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
}
void Restore(){
        for(int i=0;i<5;i++)
                _tex[i].AVI_Destroy();
        AVIFileExit();
}

///////////////////////////////////////////////////////////////////////
// Called to draw scene
void DrawAll(void){

        glBindTexture(GL_TEXTURE_2D,textures[0]);
        glBegin(GL_TRIANGLES);
                glTexCoord2f(1.0f,1.0f);
                glVertex3fv(vCorners[2]);
                glTexCoord2f(0.0f,1.0f);
                glVertex3fv(vCorners[1]);
                glTexCoord2f(0.0f,0.0f);
                glVertex3fv(vCorners[0]);

                glTexCoord2f(1.0f,1.0f);
                glVertex3fv(vCorners[2]);
                glTexCoord2f(0.0f,0.0f);
                glVertex3fv(vCorners[0]);
                glTexCoord2f(1.0f,0.0f);
                glVertex3fv(vCorners[3]);
        glEnd();
        glBindTexture(GL_TEXTURE_2D,textures[1]);
        glBegin(GL_TRIANGLES);
                glTexCoord2f(1.0f,1.0f);
                glVertex3fv(vCorners[5]);
                glTexCoord2f(0.0f,1.0f);
                glVertex3fv(vCorners[6]);
                glTexCoord2f(0.0f,0.0f);
                glVertex3fv(vCorners[7]);

                glTexCoord2f(1.0f,1.0f);
                glVertex3fv(vCorners[5]);
                glTexCoord2f(0.0f,0.0f);
                glVertex3fv(vCorners[7]);
                glTexCoord2f(1.0f,0.0f);
                glVertex3fv(vCorners[4]);
        glEnd();
        glBindTexture(GL_TEXTURE_2D,textures[2]);
        glBegin(GL_TRIANGLES);
                glTexCoord2f(1.0f,1.0f);
                glVertex3fv(vCorners[6]);
                glTexCoord2f(0.0f,1.0f);
                glVertex3fv(vCorners[2]);
                glTexCoord2f(0.0f,0.0f);
                glVertex3fv(vCorners[3]);

                glTexCoord2f(1.0f,1.0f);
                glVertex3fv(vCorners[6]);
                glTexCoord2f(0.0f,0.0f);
                glVertex3fv(vCorners[3]);
                glTexCoord2f(1.0f,0.0f);
                glVertex3fv(vCorners[7]);
        glEnd();
        glBindTexture(GL_TEXTURE_2D,textures[3]);
        glBegin(GL_TRIANGLES);
                glTexCoord2f(1.0f,1.0f);
                glVertex3fv(vCorners[5]);
                glTexCoord2f(0.0f,1.0f);
                glVertex3fv(vCorners[1]);
                glTexCoord2f(0.0f,0.0f);
                glVertex3fv(vCorners[2]);

                glTexCoord2f(1.0f,1.0f);
                glVertex3fv(vCorners[5]);
                glTexCoord2f(0.0f,0.0f);
                glVertex3fv(vCorners[2]);
                glTexCoord2f(1.0f,0.0f);
                glVertex3fv(vCorners[6]);
        glEnd();
        glBindTexture(GL_TEXTURE_2D,textures[4]);
        glBegin(GL_TRIANGLES);
                glTexCoord2f(1.0f,1.0f);
                glVertex3fv(vCorners[7]);
                glTexCoord2f(0.0f,1.0f);
                glVertex3fv(vCorners[3]);
                glTexCoord2f(0.0f,0.0f);
                glVertex3fv(vCorners[0]);

                glTexCoord2f(1.0f,1.0f);
                glVertex3fv(vCorners[7]);
                glTexCoord2f(0.0f,0.0f);
                glVertex3fv(vCorners[0]);
                glTexCoord2f(1.0f,0.0f);
                glVertex3fv(vCorners[4]);
        glEnd();
        glBindTexture(GL_TEXTURE_2D,textures[5]);
        glBegin(GL_TRIANGLES);
                glTexCoord2f(1.0f,1.0f);
                glVertex3fv(vCorners[1]);
                glTexCoord2f(0.0f,1.0f);
                glVertex3fv(vCorners[5]);
                glTexCoord2f(0.0f,0.0f);
                glVertex3fv(vCorners[4]);

                glTexCoord2f(1.0f,1.0f);
                glVertex3fv(vCorners[1]);
                glTexCoord2f(0.0f,0.0f);
                glVertex3fv(vCorners[4]);
                glTexCoord2f(1.0f,0.0f);
                glVertex3fv(vCorners[0]);
        glEnd();
}

void RenderScene(void)
{
        BITMAPINFO* pbmi;
        BYTE *pSrc;

        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

        for(int i=0;i<5;i++){
                glBindTexture(GL_TEXTURE_2D,textures[i]);
                pbmi = _tex[i].GetCurrPBMI();
                pSrc = (BYTE*)( sizeof(BITMAPINFO) + (BYTE*)pbmi );
                glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,pbmi->bmiHeader.biWidth, pbmi->bmiHeader.biHeight,0, GL_RGB, GL_UNSIGNED_BYTE, pSrc);
        }

//////
/////           End Of Binds
/////

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        glTranslatef(0.0f,0.0f,-7.0f);
        glRotatef(theta2[0],1,0,0);
        glRotatef(theta2[1],0,1,0);
        glColor3f(1.0f,1.0f,1.0f);
        DrawAll();
        glPopMatrix();
        glFinish();    // чтобы считать буфер кадров

glBindTexture(GL_TEXTURE_2D,textures[5]);
WORD _x,_y,_w=(WORD)_W,_h=(WORD)_H;
__asm{
        mov ax,_w
        xor cl,cl
label1:
        shr ax,1
        test ax,ax
        jne _next1
        mov ax,1
        shl ax,cl
        mov _w,ax
        jmp short on_H
_next1:
        inc cl
        jmp short label1
on_H:
        mov ax,_h
        xor cl,cl
label2:
        shr ax,1
        test ax,ax
        jne _next2
        mov ax,1
        shl ax,cl
        mov _h,ax
        jmp short _end
_next2:
        inc cl
        jmp short label2
_end:
}
_x = (_W-_w)/2;
_y = (_H-_h)/2;
glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGB,_x,_y,_w,_h,0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();

        glTranslatef(0.0f,0.0f,-zPos);
        glRotatef(theta[0],1,0,0);
        glRotatef(theta[1],0,1,0);

        DrawAll();

        glRotatef(-theta2[1],0,1,0);
        glRotatef(-theta2[0],1,0,0);
        glTranslatef(0.0f,0.0f,7.0f);

        glDisable(GL_TEXTURE_2D);
        glColor3f(1.0f,1.0f,1.0f);
        glutSolidSphere(0.1f,32,32);
        glEnable(GL_TEXTURE_2D);

        glPopMatrix();

        glutSwapBuffers();
}


//////////////////////////////////////////////////////////////
// For this example, it really doesn't matter what the
// projection is since we are using glWindowPos
void ChangeSize(int w, int h)
    {
        _W=w;
        _H=h;
        if(h==0)
                _H=1;
        if(w==0)
                _W=1;

        glViewport(0, 0, _W, _H);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(35.0f,(GLfloat)_W/(GLfloat)_H,1.0f,40.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}

void myIdle(){
        glutPostRedisplay();
}
void BoardKeys(unsigned char key, int x, int y)
    {
    if(key == '1')
        _tex[_gran_num].Play();
    else if(key == '2')
        _tex[_gran_num].Stop();
    else if(key == '3')
        _tex[_gran_num].Pause();

    else if(key == ' '){
        theta[0]=theta2[0];
        theta[1]=theta2[1];
    }
    else if(key == '+'){
        zPos -= 0.5f;
        if(zPos<MINZPOS)
                zPos = MINZPOS;
    }
    else if(key == '-'){
        zPos += 0.5f;
        if(zPos>MAXZPOS)
                zPos = MAXZPOS;
    }

    glutPostRedisplay();
}
void SpecialKeys(int k,int x, int y){
        if(k == GLUT_KEY_F1)
                _gran_num = 0;
        else if(k == GLUT_KEY_F2)
                _gran_num = 1;
        else if(k == GLUT_KEY_F3)
                _gran_num = 2;
        else if(k == GLUT_KEY_F4)
                _gran_num = 3;
        else if(k == GLUT_KEY_F5)
                _gran_num = 4;

        else if(k == GLUT_KEY_F10)
                camera_state = !camera_state;

        else if(k == GLUT_KEY_LEFT){
                if(!camera_state)
                        theta[1] += 5;
                else
                        theta2[1]+=5;
        }
        else if(k == GLUT_KEY_RIGHT){
                if(!camera_state)
                        theta[1] -= 5;
                else
                        theta2[1]-=5;
        }
        else if(k == GLUT_KEY_UP){
                if(!camera_state)
                        theta[0] -= 5;
                else
                        theta2[0]-=5;
        }
        else if(k == GLUT_KEY_DOWN){
                if(!camera_state)
                        theta[0] += 5;
                else
                        theta2[0]+=5;
        }

    if(theta[0] >=360) theta[0] -= 360;
    else if(theta[0] <0) theta[0] += 360;
    if(theta[1] >=360) theta[1] -= 360;
    else if(theta[1] <0) theta[1] += 360;

    if(theta2[0] >=360) theta2[0] -= 360;
    else if(theta2[0] <0) theta2[0] += 360;
    if(theta2[1] >=360) theta2[1] -= 360;
    else if(theta2[1] <0) theta2[1] += 360;

    glutPostRedisplay();
}

void my_exit(int _param){
        Restore();
        exit(_param);
}
/////////////////////////////////////////////////////////////
// Main program entrypoint
int main(int argc, char* argv[]){
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(_H ,_W);
        __glutCreateWindowWithExit("OpenGL Video Loading",my_exit);
        glutReshapeFunc(ChangeSize);
        glutDisplayFunc(RenderScene);
        glutIdleFunc(myIdle);
        glutKeyboardFunc(BoardKeys);
        glutSpecialFunc(SpecialKeys);

        SetupRC(argv[1]);
        glutMainLoop();

        Restore();
        return 0;
}
