#include <iterator>
#include <cmath>
#include "part.h"
#include <iostream>

using namespace std;

void DrawSquare(int x, int y){
    glBegin(GL_QUADS);
    glColor3f(0.4, 0, 0);
    glVertex3f(x  , -2, y  );
    glColor3f(0, 0.4, 0);
    glVertex3f(x  , -2, y+1);
    glColor3f(0, 0, 0.4);
    glVertex3f(x+1, -2, y+1);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(x+1, -2, y  );
    glEnd();
}

void part::plot(){
    switch (color) {
        case 'r':
            red;
            break;
        case 'y':
            yellow;
            break;
        case 'o':
            orange
                break;
        case 'w':
            white
                break;
        case 'b':
            blue;
            break;
        case 'g':
            green;
            break;
    }

    if(plane == 2 || plane == 4){
        glBegin(GL_POLYGON);
        glVertex3f(lower_x, lower_y, lower_z);
        glVertex3f(lower_x, lower_y, upper_z);
        glVertex3f(lower_x, upper_y, upper_z);
        glVertex3f(lower_x, upper_y, lower_z);
        glEnd();
    }else{
        glBegin(GL_QUADS);
        glVertex3f(lower_x, upper_y, lower_z);
        glVertex3f(upper_x, upper_y, lower_z);
        glVertex3f(upper_x, lower_y, upper_z);
        glVertex3f(lower_x, lower_y, upper_z);
        glEnd();
    }

}

void part::init(int p, int ps){
    plane = p;

    if(plane==1 || plane==3){
        upper_z = 1.5;
        lower_z = 1.5;
        color = 'r';

        if (plane == 3){ //if it's the orange side
            upper_z = -1.5;
            lower_z = -1.5;
            color = 'o';
        }

        lower_x = xNy[ps][0][0];
        lower_y = xNy[ps][0][1];
        upper_x = xNy[ps][1][0];
        upper_y = xNy[ps][1][1];

    }else if (plane==2 || plane==4) {
        lower_x = 1.5;
        upper_x = 1.5;
        color = 'y';
        if(plane == 4){ //white layer
            lower_x = -1.5;
            upper_x = -1.5;
            color = 'w';
        }

        lower_y = xNy[ps][0][0];
        lower_z = xNy[ps][0][1];
        upper_y = xNy[ps][1][0];
        upper_z = xNy[ps][1][1];

    }else if (plane==5 || plane==6) {
        lower_y = 1.5;
        upper_y = 1.5;
        color = 'b';

        if (plane == 6) {//green layer
            lower_y = -1.5;
            upper_y = -1.5;
            color = 'g';
        }

        lower_x = xNy[ps][0][0];
        lower_z = xNy[ps][0][1];
        upper_x = xNy[ps][1][0];
        upper_z = xNy[ps][1][1];

    }
}

void part::rotate(int ang, char ax){
    int plnSq[7] = {0,1,6,3,5,2,4};
    rotatePoint(ang, ax, 0);
    rotatePoint(ang, ax, 1);
    // plane = plnSq[plane];
}

void part::print(){
    cout<<lower_x<<endl;
    cout<<lower_y<<endl;
    cout<<lower_z<<endl;
    cout<<upper_x<<endl;
    cout<<upper_y<<endl;
    cout<<upper_z<<endl<<endl;
}

void part::rotatePoint(int ang, char axis, bool se){
    float r;
    float th1;
    float x2 = lower_x;
    float y2 = lower_y;
    float z2 = lower_z;
    float x1 = upper_x;
    float y1 = upper_y;
    float z1 = upper_z;

    if (axis =='z') {
        r = sqrt(pow(x1, 2) + pow(y1, 2));
        th1 = (atan(y1/x1)*180) / 3.14;

        y1 = r * cos((ang+th1)*3.14/180);
        x1 = r * sin((ang+th1)*3.14/180);

        r = sqrt(pow(x2, 2) + pow(y2, 2));
        th1 = (atan(y2/x2)*180) / 3.14;

        x2 = r * cos((ang+th1)*3.14/180);
        y2 = r * sin((ang+th1)*3.14/180);

        // x = x*cos(ang) - y*sin(ang);
        // y = x*sin(ang) + y*cos(ang);

    }
    // }else if (axis == 'y') {
    //     y = y*cos(ang) - z*sin(ang);
    //     z = y*sin(ang) + z*cos(ang);
    //
    // }else if (axis == 'x') {
    //     z = z*cos(ang) - x*sin(ang);
    //     x = z*sin(ang) + x*cos(ang);
    // }

    lower_x = x1;
    lower_y = y1;
    lower_z = z1;
    upper_x = x2;
    upper_y = y2;
    upper_z = z2;
}

void matMul(){
    float a[2][2];
    float b[2][2];
    float c[2][2];


    for(int m=0;m<2;m++) {
        for(int n=0;n<1;n++) {
            int temp = 0;
            for(int i=0;i<2;i++) {
                temp = temp + a[m][i]*b[i][n];

            }
            c[m][n] = temp;
        }
    }
}

// void part::rotateAxis(int a, int b, int c,int m, bool inv){
//     int d = pow((pow(b, 2) + pow(c, 2)), 0.5);
//
//     mat[m][0][0] = d;
//     mat[m][0][2] = -a;
//     mat[m][1][1] = (float)c/(float)d;
//     mat[m][1][2] = -(float)b/(float)d;
//     mat[m][2][1] = a;
//     mat[m][2][1] = (float)b/(float)d;
//     mat[m][2][2] = (float)c/(float)d;
//
//     if(inv){
//         mat[m][1][2] *= -1;
//         mat[m][2][1] *= -1;
//         mat[m][0][2] *= -1;
//         mat[m][2][1] *= -1;
//     }
// }

void room(){
    glPushMatrix();
    glTranslatef(0,0,-1.5);
    glRotatef(10, 0,1,0);

    for (int i = -8; i <8; i++) {     //along X axis
        for (int j=-8; j <8; j++) {   //along Y axis
            if( (i+j) %2 ==0){
                glColor3f(0, 0, 0);
                DrawSquare(i,j);
            }else{
                glColor3f(0.6, 0.8, 1);
                glBegin(GL_QUADS);
                glVertex3f(i  , -2, j  );
                glVertex3f(i  , -2, j+1);
                glVertex3f(i+1, -2, j+1);
                glVertex3f(i+1, -2, j  );
                glEnd();
            }

        }
    }

    glColor3f(0.345f, 0.4314f, 0.4588f);
    glBegin(GL_POLYGON);
    glColor3f(0.172f, 0.2154f, 0.2294f);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(8.0  , -2.0 , -8.0);
    glColor3f(0.345f, 0.4314f, 0.4588f);
    glVertex3f(8.0  , 4.0  , -8.0);
    glVertex3f(-8.0 , 4.0  , -8.0);
    glColor3f(0.172f, 0.2154f, 0.2294f);
    glVertex3f(-8.0 , -2.0 , -8.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.172f, 0.2154f, 0.2294f);
    glVertex3f(8.0  , -2.0 , -8.0);
    glColor3f(0.345f, 0.4314f, 0.4588f);
    glVertex3f(8.0  , -2.0 , 8.0);
    glVertex3f(8.0  , 4.0  , 8.0);
    glVertex3f(8.0  , 4.0  , -8.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(8.0  , 4.0 , 8.0);
    glVertex3f(-8.0 , 4.0 , 8.0);
    glVertex3f(-8.0 , 4.0 , -8.0);
    glVertex3f(8.0  , 4.0 , -8.0);

    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-8.0 , 4.0  , 8.0);
    glVertex3f(-8.0 , -2.0 , 8.0);
    glColor3f(0.1f, 0.2f, 0.2f);
    glVertex3f(-8.0 , -2.0 , -8.0);
    glColor3f(0.345f, 0.4314f, 0.4588f);
    glVertex3f(-8.0 , 4.0  , -8.0);
    glEnd();

    glPopMatrix();

}

void lamp(){
    glPushMatrix();
    glTranslatef(0.0, 3.6, -0.0);
    glRotatef(265, 1.0, 0.0, 0.0);
    glColor4f(1.0,1.0,1.0, 1.0);
    glutSolidCone(0.3, 0.2, 50, 50);
    glColor4f(0.0,0.0,0.0, 1.0);
    glutSolidCone(0.35, 0.25, 50, 50);
    glColor4f(1.0,1.0,1.0, 1.0);
    glutWireCone(0.36, 0.26, 10, 5);
    glPopMatrix();
}
