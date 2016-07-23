/**
*	# Contents
*		- opencv���K�v���O����1 
*			+ ��F��
*		- Source.cpp
*	# Author
*		- Mitsuhiro Mizuno
*	# LastUpdate
*		- 2016/7/23 Ver.1
*	# Since
*		- 2016/7/23	ver.1
*	# reference�@
*		- http://ishidate.my.coocan.jp/opencv_13/opencv_13.htm
*		- opencv�ɂ��摜�������� �u�k��(ISBN 978-4-06-153822-1)
*	   
**/

#define  _USE_MATH_DEFINE
#include <iostream>
#include <cmath>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

string win_src = "src";
string win_dst = "dst";
string target = "haarcascade_frontalface_alt.xml";	// �w�K�ς݃t�@�C��

int main(int argc, char **argv) {
	Mat img_src; // �擾�摜
	Mat img_dst; // �o�͉摜

	// �J�����I�[�v��  (�����ŃJ�����ԍ��w��j
	VideoCapture capture(0);
	
	// �J�������J���Ȃ��Ƃ��G���[�I��
	if (!capture.isOpened()) {
		cout << "camera error" << endl;
		return -1;
	}

	// �\���E�B���h�E�쐬
	//namedWindow(win_src	, CV_WINDOW_AUTOSIZE);// �擾�摜
	namedWindow(win_dst, CV_WINDOW_AUTOSIZE); // �o�͉摜

	while (1) {
		capture >> img_src; // �J�����f���̓ǂݍ���
		
		/* �����̊j�ƂȂ鏈�����L�q���� */
		// �摜�̃O���[��
		Mat gray_img;
		cvtColor(img_src, gray_img, CV_BGR2GRAY);
		
		// cascade�Ŋ猟�o
		vector<Rect>faces;
		CascadeClassifier cascade(target); // �w�K�ς݃t�@�C���̓ǂݎ��i���s�ꏊ�ɔz�u�j
		cascade.detectMultiScale(gray_img, faces, 1.1, 2, 2);
		
		// ���͉摜�ɘg�̕`��
		img_dst = img_src;
		for (auto it = faces.begin(); it != faces.end(); ++it) {
			rectangle(img_dst, it->tl(), it->br(), Scalar(0, 255, 255), 2, 8, 0);
		}													
		
		// �E�C���h�E�`��
		//imshow(win_src, img_src); // ���͉摜
		imshow(win_dst, img_dst);	// �o�͉摜

		// 'q'�L�[�Ńv���O�������I��
		if (waitKey(1) == 'q') {
			break;
		}
	}
	return 0;
}