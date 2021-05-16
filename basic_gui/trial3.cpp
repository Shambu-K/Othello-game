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
        std::string names[]={
            "null.png", "white.png", "black.png", "possible.png"
        };
        //enter the names of the images of pieces
        while(window.isOpen()){
                sf::Event event;
                while(window.pollEvent(event)){
                        if(event.type == sf::Event::Closed){
                            window.close();
                        }
                }
                sf::Vector2i position = sf::Mouse::getPosition(window);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    int locationx=position.x/60;
                    int locationy=(position.y-20)/60;
                    if(is_mouse_on_board(position))
                    {
                        level[locationx + locationy*8]=num_of_times%2 + 1;
                        num_of_times++;
                        while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {}
                       
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
                window.draw(text);
                window.display();      
                //displaying the window  
        }     

}