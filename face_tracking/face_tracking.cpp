/**
*	# Contents
*		- opencv練習プログラム1 
*			+ 顔認識
*		- Source.cpp
*	# Author
*		- Mitsuhiro Mizuno
*	# LastUpdate
*		- 2016/7/23 Ver.1
*	# Since
*		- 2016/7/23	ver.1
*	# reference　
*		- http://ishidate.my.coocan.jp/opencv_13/opencv_13.htm
*		- opencvによる画像処理入門 講談社(ISBN 978-4-06-153822-1)
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
string target = "haarcascade_frontalface_alt.xml";	// 学習済みファイル

int main(int argc, char **argv) {
	Mat img_src; // 取得画像
	Mat img_dst; // 出力画像

	// カメラオープン  (引数でカメラ番号指定）
	VideoCapture capture(0);
	
	// カメラを開けないときエラー終了
	if (!capture.isOpened()) {
		cout << "camera error" << endl;
		return -1;
	}

	// 表示ウィンドウ作成
	//namedWindow(win_src	, CV_WINDOW_AUTOSIZE);// 取得画像
	namedWindow(win_dst, CV_WINDOW_AUTOSIZE); // 出力画像

	while (1) {
		capture >> img_src; // カメラ映像の読み込み
		
		/* ここの核となる処理を記述する */
		// 画像のグレー化
		Mat gray_img;
		cvtColor(img_src, gray_img, CV_BGR2GRAY);
		
		// cascadeで顔検出
		vector<Rect>faces;
		CascadeClassifier cascade(target); // 学習済みファイルの読み取り（実行場所に配置）
		cascade.detectMultiScale(gray_img, faces, 1.1, 2, 2);
		
		// 入力画像に枠の描写
		img_dst = img_src;
		for (auto it = faces.begin(); it != faces.end(); ++it) {
			rectangle(img_dst, it->tl(), it->br(), Scalar(0, 255, 255), 2, 8, 0);
		}													
		
		// ウインドウ描写
		//imshow(win_src, img_src); // 入力画像
		imshow(win_dst, img_dst);	// 出力画像

		// 'q'キーでプログラムを終了
		if (waitKey(1) == 'q') {
			break;
		}
	}
	return 0;
}