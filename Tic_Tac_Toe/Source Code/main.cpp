#include<SFML/Graphics/RenderWindow.hpp>
#include<SFML/Window/Event.hpp>
#include<iostream>
#include<SFML/Graphics/VertexArray.hpp>
#include<SFML/Graphics/Color.hpp>
#include<SFML/Graphics/RectangleShape.hpp>
#include<SFML/Graphics/Text.hpp>
#include<SFML/Audio/Music.hpp>
#include<SFML/Graphics/Font.hpp>
#include<SFML/Graphics/CircleShape.hpp>
#include<SFML/Graphics/Image.hpp>
sf::Text XPlyaer_Text[5],Draw_Text,OPlayer_Text[4],XPlayerWin,OPlayerWin;
sf::RectangleShape Selected_Area;
int Index_Selected_Area_x,Index_Selected_Area_y;
sf::RectangleShape Grid_Lines[4];
int Dimension_LineGrid=8,Radius_Circle=10;
const int Dimension_RenderWindow=400+2*Dimension_LineGrid;
bool is_XorO=true;
sf::RenderWindow app(sf::VideoMode(Dimension_RenderWindow,Dimension_RenderWindow+200),"Tic-Tac-Toe Game");
sf::RectangleShape Line_End_GameSpace;
sf::Text text1,text2;
sf::CircleShape circle;
sf::Font font;
int Counter_X,Counter_O,Shift_X=35,Shift_Y=7;
int Index_XPlayer[5][2],Index_OPlayer[5][2];
sf::Music music;
sf::Image image;
enum Search{X=1,O=2,A=3};
class Tic_Tac_Toe_Game
{
private:
    void SetLines()
    {
        Grid_Lines[0].setPosition(sf::Vector2f(Dimension_RenderWindow/3,0));
        Grid_Lines[1].setPosition(sf::Vector2f(2*Dimension_RenderWindow/3,0));
        Grid_Lines[2].setPosition(sf::Vector2f(0,Dimension_RenderWindow/3));
        Grid_Lines[3].setPosition(sf::Vector2f(0,2*Dimension_RenderWindow/3));
        for(int i=0;i<2;i++)
            Grid_Lines[i].setSize(sf::Vector2f(Dimension_LineGrid,Dimension_RenderWindow));
        for(int i=2;i<4;i++)
            Grid_Lines[i].setSize(sf::Vector2f(Dimension_RenderWindow,Dimension_LineGrid));
        Selected_Area.setSize(sf::Vector2f(Dimension_RenderWindow/3,Dimension_RenderWindow/3));
        Selected_Area.setFillColor(sf::Color::Red);
        Line_End_GameSpace.setSize(sf::Vector2f(Dimension_RenderWindow,Dimension_LineGrid));
        Line_End_GameSpace.setPosition(sf::Vector2f(0,Dimension_RenderWindow));
        Line_End_GameSpace.setFillColor(sf::Color::White);
    }
    void set_XorY()
    {
        if(is_XorO)
        {
            XPlyaer_Text[Counter_X].setFont(font);
            XPlyaer_Text[Counter_X].setString("X");
            XPlyaer_Text[Counter_X].setCharacterSize(80);
            XPlyaer_Text[Counter_X].setPosition(sf::Vector2f(Index_XPlayer[Counter_X][0]*Dimension_RenderWindow/3+Shift_X,Index_XPlayer[Counter_X][1]*Dimension_RenderWindow/3+Shift_Y));
        }
        else
        {
            OPlayer_Text[Counter_O].setFont(font);
            OPlayer_Text[Counter_O].setString("O");
            OPlayer_Text[Counter_O].setCharacterSize(80);
            OPlayer_Text[Counter_O].setPosition(sf::Vector2f(Index_OPlayer[Counter_O][0]*Dimension_RenderWindow/3+Shift_X,Index_OPlayer[Counter_O][1]*Dimension_RenderWindow/3+Shift_Y));
        }
    }
    void set_DrawText()
    {
        Draw_Text.setFont(font);
        Draw_Text.setString("Draw");
        Draw_Text.setCharacterSize(50);
        Draw_Text.setPosition(sf::Vector2f(Dimension_RenderWindow/2,Dimension_RenderWindow+60));
    }
    bool SearchIndexatArray(int x,int y,Search s)
    {
        if((s==Search::A)||(s==Search::X))
        {
            for(int i=0;i<=Counter_X;i++)
                if((Index_XPlayer[i][0]==x)&&(Index_XPlayer[i][1]==y))
                    return true;
        }
        if((s==Search::A)||(s==Search::O))
        {
            for(int i=0;i<=Counter_O;i++)
                if((Index_OPlayer[i][0]==x)&&(Index_OPlayer[i][1]==y))
                    return true;
        }
        return false;
    }
    bool TestsPlayerXWin()
    {
        if((SearchIndexatArray(0,0,Search::X))&&(SearchIndexatArray(0,1,Search::X))&&(SearchIndexatArray(0,2,Search::X)))
            return true;
        if((SearchIndexatArray(1,0,Search::X))&&(SearchIndexatArray(1,1,Search::X))&&(SearchIndexatArray(1,2,Search::X)))
            return true;
        if((SearchIndexatArray(2,0,Search::X))&&(SearchIndexatArray(2,1,Search::X))&&(SearchIndexatArray(2,2,Search::X)))
            return true;
        if((SearchIndexatArray(0,0,Search::X))&&(SearchIndexatArray(1,0,Search::X))&&(SearchIndexatArray(2,0,Search::X)))
            return true;
        if((SearchIndexatArray(0,1,Search::X))&&(SearchIndexatArray(1,1,Search::X))&&(SearchIndexatArray(2,1,Search::X)))
            return true;
        if((SearchIndexatArray(0,2,Search::X))&&(SearchIndexatArray(1,2,Search::X))&&(SearchIndexatArray(2,2,Search::X)))
            return true;
        if((SearchIndexatArray(0,0,Search::X))&&(SearchIndexatArray(1,1,Search::X))&&(SearchIndexatArray(2,2,Search::X)))
            return true;
        if((SearchIndexatArray(0,2,Search::X))&&(SearchIndexatArray(1,1,Search::X))&(SearchIndexatArray(2,0,Search::X)))
            return true;
        return false;
    }
    bool TestsPlayerOWin()
    {
        if((SearchIndexatArray(0,0,Search::O))&&(SearchIndexatArray(0,1,Search::O))&&(SearchIndexatArray(0,2,Search::O)))
            return true;
        if((SearchIndexatArray(1,0,Search::O))&&(SearchIndexatArray(1,1,Search::O))&&(SearchIndexatArray(1,2,Search::O)))
            return true;
        if((SearchIndexatArray(2,0,Search::O))&&(SearchIndexatArray(2,1,Search::O))&&(SearchIndexatArray(2,2,Search::O)))
            return true;
        if((SearchIndexatArray(0,0,Search::O))&&(SearchIndexatArray(1,0,Search::O))&&(SearchIndexatArray(2,0,Search::O)))
            return true;
        if((SearchIndexatArray(0,1,Search::O))&&(SearchIndexatArray(1,1,Search::O))&&(SearchIndexatArray(2,1,Search::O)))
            return true;
        if((SearchIndexatArray(0,2,Search::O))&&(SearchIndexatArray(1,2,Search::O))&&(SearchIndexatArray(2,2,Search::O)))
            return true;
        if((SearchIndexatArray(0,0,Search::O))&&(SearchIndexatArray(1,1,Search::O))&&(SearchIndexatArray(2,2,Search::O)))
            return true;
        if((SearchIndexatArray(0,2,Search::O))&&(SearchIndexatArray(1,1,Search::O))&&(SearchIndexatArray(2,0,Search::O)))
            return true;
        return false;
    }
    void set_PlayerXWinText()
    {
        XPlayerWin.setFont(font);
        XPlayerWin.setString("X Win");
        XPlayerWin.setCharacterSize(50);
        XPlayerWin.setPosition(Draw_Text.getPosition());
    }
    void set_PlayerOWinText()
    {
        OPlayerWin.setFont(font);
        OPlayerWin.setString("O Win");
        OPlayerWin.setCharacterSize(50);
        OPlayerWin.setPosition(XPlayerWin.getPosition());
    }
public:
    Tic_Tac_Toe_Game()
    {
        Counter_X=Counter_O=-1;
        circle.setRadius(Radius_Circle);
        circle.setPointCount(3);
        circle.setRotation(-90);
        Index_Selected_Area_x=0;
        Index_Selected_Area_y=0;
        SetLines();
        if(!font.loadFromFile("BELLB.ttf"))
        {
            system("cls");
            std::cout<<"Error in Loading (BELLB.ttf) or not found\n";
            return;
        }
        if(!music.openFromFile("sound.wav"))
        {
            system("cls");
            std::cout<<"Error in Loading (sound.wav) or not found\n";
            return;
        }
        if(!image.loadFromFile("Icon RenderWindow.png"))
        {
            system("cls");
            std::cout<<"Error in Loading (Icon RenderWindow.png) or not found\n";
            return;
        }
        app.setIcon(image.getSize().x,image.getSize().y,image.getPixelsPtr());
        text1.setFont(font);
        text2.setFont(font);
        text1.setString("X");
        text2.setString("O");
        text1.setPosition(sf::Vector2f(40,Dimension_RenderWindow+40));
        text2.setPosition(sf::Vector2f(40,Dimension_RenderWindow+100));
        text1.setCharacterSize(50);
        text2.setCharacterSize(50);
        music.play();
        set_DrawText();
        set_PlayerXWinText();
        set_PlayerOWinText();
        music.setLoop(true);
        app.setFramerateLimit(60);
        bool is_Draw=false;
        while(app.isOpen())
        {
            sf::Event event;
            while(app.pollEvent(event))
            {
                if((event.type==event.Closed)||((event.type==sf::Event::KeyPressed)&&(event.key.code==sf::Keyboard::Space)))
                {
                    music.stop();
                    app.close();
                }
                if(event.type==sf::Event::KeyPressed)
                {
                    if(event.key.code==sf::Keyboard::P)
                    {
                        if(music.getStatus()==sf::Music::Status::Playing)
                            music.pause();
                        else if(music.getStatus()==sf::Music::Status::Paused)
                            music.play();
                    }
                    if((event.key.code==sf::Keyboard::Up)||(event.key.code==sf::Keyboard::W))
                    {
                        Index_Selected_Area_y--;
                        if(SearchIndexatArray(Index_Selected_Area_x,Index_Selected_Area_y,Search::A))
                            Index_Selected_Area_y--;
                        if(Index_Selected_Area_y<0)
                        {
                            Index_Selected_Area_y=2;
                            Index_Selected_Area_x--;
                        }
                        if(Index_Selected_Area_x<0)
                            Index_Selected_Area_x=2;
                    }
                    if((event.key.code==sf::Keyboard::Down)||(event.key.code==sf::Keyboard::S))
                    {
                        Index_Selected_Area_y++;
                        if(SearchIndexatArray(Index_Selected_Area_x,Index_Selected_Area_y,Search::A))
                            Index_Selected_Area_y++;
                        if(Index_Selected_Area_y>2)
                        {
                            Index_Selected_Area_y=0;
                            Index_Selected_Area_x++;
                        }
                        if(Index_Selected_Area_x>2)
                            Index_Selected_Area_x=0;
                    }
                    if((event.key.code==sf::Keyboard::Left)||(event.key.code==sf::Keyboard::A))
                    {
                        Index_Selected_Area_x--;
                        if(SearchIndexatArray(Index_Selected_Area_x,Index_Selected_Area_y,Search::A))
                            Index_Selected_Area_x--;
                        if(Index_Selected_Area_x<0)
                        {
                            Index_Selected_Area_x=2;
                            Index_Selected_Area_y--;
                        }
                        if(Index_Selected_Area_y<0)
                            Index_Selected_Area_y=2;
                    }
                    if((event.key.code==sf::Keyboard::Enter)&&(Counter_O+Counter_X<=6)&&(!TestsPlayerXWin())&&(!TestsPlayerOWin())&&(!is_Draw))
                    {
                        if(is_XorO)
                        {
                            Counter_X++;
                            Index_XPlayer[Counter_X][0]=Index_Selected_Area_x;
                            Index_XPlayer[Counter_X][1]=Index_Selected_Area_y;
                        }
                        else
                        {
                            Counter_O++;
                            Index_OPlayer[Counter_O][0]=Index_Selected_Area_x;
                            Index_OPlayer[Counter_O][1]=Index_Selected_Area_y;
                        }
                        set_XorY();
                        is_XorO=!is_XorO;
                        Index_Selected_Area_x++;
                        if(Index_Selected_Area_x>2)
                        {
                            Index_Selected_Area_x=0;
                            Index_Selected_Area_y++;
                        }
                        if(Index_Selected_Area_y>2)
                            Index_Selected_Area_y=0;
                    }
                    if((event.key.code==sf::Keyboard::Right)||(event.key.code==sf::Keyboard::D))
                    {
                        Index_Selected_Area_x++;
                        if(SearchIndexatArray(Index_Selected_Area_x,Index_Selected_Area_y,Search::A))
                            Index_Selected_Area_x++;
                        if(Index_Selected_Area_x>2)
                        {
                            Index_Selected_Area_x=0;
                            Index_Selected_Area_y++;
                        }
                        if(Index_Selected_Area_y>2)
                            Index_Selected_Area_y=0;
                    }
                    if(event.key.code==sf::Keyboard::Add)
                    {
                        auto newUpVolume=music.getVolume()+1;
                        if(newUpVolume>100)
                            newUpVolume=100;
                        music.setVolume(newUpVolume);
                    }
                    if(event.key.code==sf::Keyboard::Subtract)
                    {
                        auto newDownVolume=music.getVolume()-1;
                        if(newDownVolume<0)
                            newDownVolume=0;
                        music.setVolume(newDownVolume);
                    }
                    if(event.key.code==sf::Keyboard::R)
                    {
                        Counter_X=Counter_O=-1;
                        Index_Selected_Area_x=0;
                        Index_Selected_Area_y=0;
                        for(int i=0;i<5;i++)
                        {
                            Index_XPlayer[i][0]=0;
                            Index_XPlayer[i][1]=0;
                            Index_OPlayer[i][0]=0;
                            Index_OPlayer[i][1]=0;
                        }
                        is_XorO=true;
                    }
                }
            }
            while(SearchIndexatArray(Index_Selected_Area_x,Index_Selected_Area_y,Search::A)&&(Counter_O+Counter_X<=6))
            {
                Index_Selected_Area_x++;
                if(Index_Selected_Area_x>2)
                {
                    Index_Selected_Area_y++;
                    Index_Selected_Area_x=0;
                }
                if(Index_Selected_Area_y>2)
                {
                    Index_Selected_Area_y=0;
                    Index_Selected_Area_x=0;
                }
            }
            Selected_Area.setPosition(sf::Vector2f(Index_Selected_Area_x*Dimension_RenderWindow/3,Index_Selected_Area_y*Dimension_RenderWindow/3));
            if(Index_Selected_Area_x>2)
                    Index_Selected_Area_x=0;
            if(is_XorO)
                circle.setPosition(sf::Vector2f(text1.getPosition().x+60,text1.getPosition().y+40));
            else circle.setPosition(sf::Vector2f(text2.getPosition().x+60,text2.getPosition().y+45));
            app.clear();
            if(Counter_X+Counter_O<=6)
                app.draw(Selected_Area);
            for(int i=0;i<=Counter_X;i++)
                app.draw(XPlyaer_Text[i]);
            for(int i=0;i<=Counter_O;i++)
                app.draw(OPlayer_Text[i]);
            app.draw(text1);
            app.draw(text2);
            app.draw(circle);
            for(int i=0;i<4;i++)
                app.draw(Grid_Lines[i]);
            app.draw(Line_End_GameSpace);
            if(TestsPlayerXWin())
                app.draw(XPlayerWin);
            if(TestsPlayerOWin())
                app.draw(OPlayerWin);
            if((!TestsPlayerXWin())&&(!TestsPlayerOWin())&&(Counter_O+Counter_X==7))
            {
                app.draw(Draw_Text);
                is_Draw=true;
            }
            app.display();
        }
    }
};
int main(int argc,char *argv[])
{
    Tic_Tac_Toe_Game game;
    return 0;
}
