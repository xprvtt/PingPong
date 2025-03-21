#include <SFML/Graphics.hpp>
#include "main.h"


using namespace sf;

int main()
{

    setlocale(LC_ALL, "ru");

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                                         //
    // ���������� ��������� ������                                                                                       //
    // ����� ������                                                                                                      //
    unsigned int SizeWindowLength = 1920;                                                                                //
    // ������ ������                                                                                                     //
    unsigned int SizeWindowHeight = 1024;                                                                                //                                                                                                                         
    /// �������� ����������� ���                                                                                         //
    unsigned int CountCell = 15;                                                                                         //
                                                                                                                         //
    /// ����� ����� ����                                                                                                 //
    const float CellWindowLength = SizeWindowLength / CountCell;                                                         //
    /// ������ ����� ����                                                                                                //
    const float CellWindowHeight = SizeWindowHeight / CountCell;                                                         //
                                                                                                                         //
    // ������ ��������                                                                                                   //
    float SpeedMain = 8.0f;                                                                                              //
    // ��������� �������� ��� ���� � ������� �������                                                                     //
    float SpeedMainCorrectShapeBlack = 1.9f;                                                                             //
    // ��������� �������� ��� ���� � ���������� �������                                                                  //
    float SpeedMainCorrectShapeWhite = 1.1f;                                                                             //
                                                                                                                         //
    /// �������� ������� ����                                                                                            //
    Vector2f SpeedBlackShape(SpeedMain * SpeedMainCorrectShapeBlack,  SpeedMain * SpeedMainCorrectShapeBlack);           //
    /// �������� ������ ����                                                                                             //
    Vector2f SpeedWhiteShape(SpeedMain * SpeedMainCorrectShapeWhite,  SpeedMain * SpeedMainCorrectShapeWhite);           //
                                                                                                                         //
    // ������ ��� �����                                                                                                  //
    int Radiusball = 10;                                                                                                 //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





    // ���������� ���������� ��������� ������� ����������
    // White \ Black
    // true = BLACK !!!
    vector<bool> CenterZoneBla�k = IdentifyCentralZone(CountCell);



    /////////////////////////////////////////////////////////////////////////////////////////////
    vector<RectangleShape> ZONE;                                                               //
    //��������� ������ ���                                                                     //
    for (int row = 0, count = 0; row < CountCell; row++)                                       //
    {                                                                                          //
        for (int coll = 0; coll < CountCell; coll++)                                           //
        {                                                                                      //
            RectangleShape Cell(Vector2f(CellWindowLength, CellWindowHeight));                 //
            Cell.setOutlineThickness(-1);                                                      //
            Cell.setPosition(Vector2f(coll * CellWindowLength, row * CellWindowHeight));       //
                                                                                               //
            if (CenterZoneBla�k[count])                                                        //
            {                                                                                  //
                Cell.setOutlineColor(Color::White);                                            //
                Cell.setFillColor(Color::Black);                                               //
            }                                                                                  //
            else                                                                               //
            {                                                                                  //
                Cell.setOutlineColor(Color::Black);                                            //
                Cell.setFillColor(Color::White);                                               //
            }                                                                                  //
                                                                                               //
            ZONE.push_back(Cell);                                                              //
            count++;                                                                           //
        }                                                                                      //
    }                                                                                          //
    /////////////////////////////////////////////////////////////////////////////////////////////

    srand(time(NULL));

    CircleShape ballWhite;
    ballWhite.setOutlineThickness(1);
    ballWhite.setOutlineColor(Color::Black);
    ballWhite.setRadius(Radiusball);
    ballWhite.setFillColor(Color::White);
    ballWhite.setPosition(Vector2f(SizeWindowLength / 2 + rand()%50, SizeWindowHeight / 2 + rand() % 50));

    CircleShape ballBlack;
    ballBlack.setOutlineThickness(1);
    ballBlack.setOutlineColor(Color::White);
    ballBlack.setRadius(Radiusball);
    ballBlack.setFillColor(Color::Black);
    ballBlack.setPosition(Vector2f(rand() % SizeWindowLength, 10.0));


    RenderWindow window(VideoMode({ SizeWindowLength, SizeWindowHeight }), "PingPong");
    window.setFramerateLimit(60);

    // ���������� ������� ������ ��� ��������� �������������
    RectangleShape WindowBound(Vector2f(SizeWindowLength, SizeWindowHeight));
    WindowBound.setPosition(Vector2f(0.0f, 0.0f));
    
    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
            {
                window.close();
            }
        }
        ballBlack.move(SpeedBlackShape);
        ballWhite.move(SpeedWhiteShape);        

        for (auto& cell : ZONE)
        {
            // ���������� ������������ ��� ������� ���� \ ������� �������
            if (ballBlack.getGlobalBounds().findIntersection(cell.getGlobalBounds()) && cell.getFillColor() == ballBlack.getFillColor())
            {
                cell.setFillColor(Color::White);
                cell.setOutlineColor(Color::Black);
                SpeedBlackShape = SpeedBlackShape.rotatedBy(degrees(90));
            }
            if (!ballBlack.getGlobalBounds().findIntersection(WindowBound.getGlobalBounds()))
            {
                SpeedBlackShape = SpeedBlackShape.rotatedBy(degrees(90));
            }
            // ���������� ������������ ��� ������ ���� \ ���������� �������
            if (ballWhite.getGlobalBounds().findIntersection(cell.getGlobalBounds()) && cell.getFillColor() == ballWhite.getFillColor())
            {
                cell.setFillColor(Color::Black);
                cell.setOutlineColor(Color::White);
                SpeedWhiteShape = SpeedWhiteShape.rotatedBy(degrees(90));
            }
            if (!ballWhite.getGlobalBounds().findIntersection(WindowBound.getGlobalBounds()))
            {
                SpeedWhiteShape = SpeedWhiteShape.rotatedBy(degrees(90));
            }
            
        }        

        window.clear(Color::White);
        for (const auto& cell : ZONE)
        {
            window.draw(cell);
        }
        window.draw(ballBlack);
        window.draw(ballWhite);
        window.display();
    }
    return 0;
}
