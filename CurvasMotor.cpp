#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace cv;
using namespace std;

list<pair<double, double> > curvePoints;

int pixel_x, pixel_y;

void mouseCallback(int event, int x, int y, int flags, void *userdata)
{
    if  ( event == EVENT_LBUTTONDOWN )
    {
        pixel_x = x;
        pixel_y = y;
    }
}

void savePoints()
{
    static int state = 0;
    
    static int pixel_x0, pixel_y0;
    static double img_x0, img_y0;
    static double mx, my;

    double img_x, img_y;

    switch(state)
    {
        case 0:
            cout << "Insira o valor de x: ";
            cin >> img_x0;

            cout << "Insira o valor de y: ";
            cin >> img_y0;

            pixel_x0 = pixel_x;
            pixel_y0 = pixel_y;

            state++;
            break;
        case 1:
            cout << "Insira o valor de x: ";
            cin >> img_x;

            cout << "Insira o valor de y: ";
            cin >> img_y;

            mx = (img_x - img_x0)/(pixel_x - pixel_x0);
            my = (img_y - img_y0)/(pixel_y - pixel_y0);

            state++;            
            break;
        default:
            img_x = mx*(pixel_x - pixel_x0) + img_x0;
            img_y = my*(pixel_y - pixel_y0) + img_y0;

            curvePoints.push_back(make_pair(img_x, img_y));

            cout << img_x << ' ' << img_y << endl;
    }
}

void writeCSV(string name)
{
    ofstream file;

    name = name + ".csv";

    file.open(name);

    while(curvePoints.size())
    {
        file << curvePoints.front().first << ',' << curvePoints.front().second << endl;
        curvePoints.pop_front();
    }

    file.close();
}

int main(int argc, char *argv[])
{
    string curveName = "";
    char c;

    vector<pair<int, int> > scalePoints;

    Mat im;

    im = imread(argv[1], IMREAD_COLOR);

    pixel_x = pixel_y = -1;

    namedWindow("Display", WINDOW_AUTOSIZE);
    setMouseCallback("Display", mouseCallback, NULL);

    for(;;)
    {
        cout << "Digite o nome da curva ou enter para sair." << endl;
        while((c = cin.get()) != '\n')
            curveName += c; 

        if(curveName.empty()) break;

        for(;;)
        {
            imshow("Display", im);
            if(waitKey(30) == 27) break;

            if(pixel_x >= 0 && pixel_y >= 0)
            {
                setMouseCallback("Display", NULL, NULL);

                savePoints();

                pixel_x = pixel_y = -1;
            }
            else
                setMouseCallback("Display", mouseCallback, NULL);
        }

        writeCSV(curveName);
    }
    return 0;
}