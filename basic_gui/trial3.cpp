#include<SFML/Graphics.hpp>
#include<iostream>

void print_all(std::string* names, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height,sf::RenderWindow* window)
{
    for(unsigned i=0;i<width;i++)
    {
        for(unsigned j=0;j<height;j++)
        {
            unsigned tilenumber = tiles[i+j*width];
            //getting the piece configuration at a location from board configuration
            sf::Texture texture;
            if(!texture.loadFromFile(names[tilenumber]))
                return ;
            //getting information from images of pieces of board
            sf::Sprite sprite(texture);
            texture.setSmooth(true);
            sprite.setPosition(i*tileSize.x*1.f,20.f+j*tileSize.y*1.f);
            window->draw(sprite);
            //adding the pieces to window here
        }
    }
}
bool is_mouse_on_board(sf::Vector2i position)
{
    if((0<position.x&&position.x)<480&&(20<position.y&&position.y<500))
        return true;
    else return false;
}
void no_legal_moves(sf::Vector2i position_window,sf::RenderWindow *window,sf::Font font)
{
    
    sf::Vector2i location;
    location.x =position_window.x/60;
    location.y =(position_window.y-20)/60;
    sf::Vector2u window_size= window->getSize();
    sf::Vector2i window_position = window->getPosition();
    
    sf::RenderWindow No_moves(sf::VideoMode(window_size.x/2,window_size.y/3),"No legal moves");
    No_moves.setVerticalSyncEnabled(true);
    sf::Vector2u No_moves_size =No_moves.getSize();
    sf::Vector2i window1_position;
    window1_position.x=(window_size.x - No_moves_size.x)/2 +window_position.x;
    window1_position.y=(window_size.y - No_moves_size.y)/2 + window_position.y;
    No_moves.setPosition(window1_position);

    sf::RectangleShape rectangle (sf::Vector2f(No_moves_size.x/6,No_moves_size.y/6));
    rectangle.setFillColor(sf::Color(200,200,200));
    sf::Vector2f rectangle_size = rectangle.getSize();
    rectangle.setPosition(sf::Vector2f(4*No_moves_size.x/5,4*No_moves_size.y/5));
    sf::FloatRect rectangle_boundaries= rectangle.getGlobalBounds();
    //rectangle.setOutlineColor(sf::Color::Black);
    //rectangle.setOutlineThickness(1);

    sf::Text text;
    text.setFont(font);
    text.setString("No legal moves possible");
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::Black);
    text.setPosition((No_moves_size.x)/10 ,(No_moves_size.y)/3);

    sf::Text ok;
    ok.setFont(font);
    ok.setString("Ok");
    ok.setCharacterSize(14);
    ok.setFillColor(sf::Color::Black);
    ok.setPosition(5*(No_moves_size.x)/6,5*(No_moves_size.y)/6);
    sf::FloatRect ok_boundaries= ok.getGlobalBounds();

    sf::RectangleShape ok_rectangle (sf::Vector2f(ok_boundaries.width*1.3,ok_boundaries.height*1.1));
    ok_rectangle.setPosition(sf::Vector2f(ok_boundaries.left,ok_boundaries.top));
    ok_rectangle.setOutlineColor(sf::Color::Black);
    ok_rectangle.setOutlineThickness(0.5);
    ok_rectangle.setFillColor(sf::Color::Transparent);

    while (No_moves.isOpen())
    {
        sf::Event event;
        while (No_moves.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
            {
                No_moves.close();
            }
        }
        sf::Vector2i position = sf::Mouse::getPosition(No_moves);
        No_moves.clear(sf::Color(240,240,240));
        
        No_moves.draw(rectangle);
        No_moves.draw(ok);
        if(rectangle_boundaries.left<position.x && position.x<(rectangle_boundaries.left + rectangle_boundaries.width) && rectangle_boundaries.top<position.y&&
                    position.y<(rectangle_boundaries.top + rectangle_boundaries.height))        
        {
            No_moves.draw(ok_rectangle);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&No_moves.hasFocus())
            {
                No_moves.close();
                while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    /* code */
                }
                
            }

        }
        No_moves.draw(text);
        No_moves.display();
    }
    
    
}
int main(){
        sf::RenderWindow window(sf::VideoMode(480,500),"Trial3");  
        //creating window
        window.setVerticalSyncEnabled(true);
        //setting the window
        sf::Font font;
        if(!font.loadFromFile("arial.ttf"))
            return -1;
        sf::Text text;

        // select the font
        text.setFont(font); // font is a sf::Font

        // set the string to display
        text.setString("New Game");

        // set the character size
        text.setCharacterSize(18); // in pixels, not points!
        
        // set the color
        text.setFillColor(sf::Color::Black);

        // set the text style
       // text.setStyle(sf::Text::);

        text.setPosition(0.f,0.f);
        sf::FloatRect floatrec= text.getGlobalBounds();
        sf::RectangleShape rectangle(sf::Vector2f(floatrec.width,20.f));
        rectangle.setFillColor(sf::Color::Blue);
        rectangle.setPosition(sf::Vector2f(0.f,0.f));
         int level_base[] =
        {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 3, 0, 0, 0,
        0, 0, 0, 2, 1, 3, 0, 0,
        0, 0, 3, 1, 2, 0, 0, 0,
        0, 0, 0, 3, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        };
        int level[64];
        for(unsigned i=0;i<64;i++)
        {
            level[i]=level_base[i];
        }
        //board configuration
        int num_of_times=0;
        int num=0;
        bool turned =false;
        std::string names[]={
            "null.png", "white.png", "black.png", "possible.png"
        };
        //enter the names of the images of pieces
        while(window.isOpen()){
                sf::Event event;
                while(window.pollEvent(event))
                {
                        if(event.type == sf::Event::Closed)
                        {
                            window.close();
                        }
                }
                sf::Vector2i position = sf::Mouse::getPosition(window);
                
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&window.hasFocus())
                {
                    sf::Vector2u location;
                    location.x=position.x/60;
                    location.y=(position.y-20)/60;
                    if(is_mouse_on_board(position))
                    {
                        level[location.x + location.y*8]=num_of_times%2 + 1;
                        num_of_times++;
                        turned=true;
                       
                    }
                    if((0<position.x&&position.x<floatrec.width)&&(0<position.y&&position.y<20))
                    {
                        for(unsigned i=0;i<64;i++)
                        {
                            level[i]=level_base[i];
                        }
                    }
                }
                //setting up command when left mouse button is clicked

                window.clear(sf::Color::White); 
                print_all(names,sf::Vector2u(60.f,60.f),level,8,8,&window);
                //setting up the window
                if((0<position.x&&position.x<floatrec.width)&&(0<position.y&&position.y<20))
                {
                    window.draw(rectangle);
                }
                num++;
              
                window.draw(text);
                window.display();      
                //displaying the window  
                if(num==1)
                {
                    no_legal_moves(position,&window,font);
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&window.hasFocus()&&is_mouse_on_board(position)&&turned)
                {                    
                    while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {}                    
                    turned=false;
                }
        }     

}