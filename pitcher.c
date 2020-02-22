#include <stdlib.h>
#include <GL/glut.h>

#define W 10             /* 地面の幅　　　　　　　 */
#define D 10             /* 地面の長さ　　　　　　 */
#define QX 0.0           /* 球の初期位置のｘ座標値 */
#define QY 1.5           /* 球の初期位置のｙ座標値 */
#define QZ (-5.0)        /* 球の初期位置のｚ座標値 */
#define G (-9.8)         /* 重力加速度　　　　　　 */
#define V 25.0           /* 初速度　　　　　　　　 */
#define TSTEP 0.01       /* フレームごとの時間　　 */
#define R 0.1            /* ボールの半径　　　　　 */

/*
 * 地面を描く
 */
static void myGround(double height)
{
  const static GLfloat ground[][4] = {
    { 0.6, 0.6, 0.6, 1.0 },
    { 0.3, 0.3, 0.3, 1.0 }
  };

  int i, j;

  glBegin(GL_QUADS);
  glNormal3d(0.0, 1.0, 0.0);
  for (j = -D / 2; j < D / 2; ++j) {
    for (i = -W / 2; i < W / 2; ++i) {
      glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i + j) & 1]);
      glVertex3d((GLdouble)i, height, (GLdouble)j);
      glVertex3d((GLdouble)i, height, (GLdouble)(j + 1));
      glVertex3d((GLdouble)(i + 1), height, (GLdouble)(j + 1));
      glVertex3d((GLdouble)(i + 1), height, (GLdouble)j);
    }
  }
  glEnd();
}

/*
 * 画面表示
 */
static void display(void)
{
  const static GLfloat white[] = { 0.8, 0.8, 0.8, 1.0 };    /* 球の色 */
  const static GLfloat lightpos[] = { 3.0, 4.0, 5.0, 1.0 }; /* 光源の位置 */
  static double px = QX, py = QY, pz = QZ;                  /* 球の位置 */

  /* 画面クリア */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* モデルビュー変換行列の初期化 */
  glLoadIdentity();

  /* 光源の位置を設定 */
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

  /* 視点の移動（物体の方を奥に移す）*/
  glTranslated(0.0, -QY, -D);

  /* シーンの描画 */
  myGround(0.0);
  glTranslated(px, py, pz);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
  glutSolidSphere(R, 16, 8);

  glFlush();
}

static void resize(int w, int h)
{
  /* ウィンドウ全体をビューポートにする */
  glViewport(0, 0, w, h);

  /* 透視変換行列の指定 */
  glMatrixMode(GL_PROJECTION);

  /* 透視変換行列の初期化 */
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

  /* モデルビュー変換行列の指定 */
  glMatrixMode(GL_MODELVIEW);
}

static void keyboard(unsigned char key, int x, int y)
{
  /* ESC か q をタイプしたら終了 */
  if (key == '\033' || key == 'q') {
    exit(0);
  }
}

static void init(void)
{
  /* 初期設定 */
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();
  return 0;
}
