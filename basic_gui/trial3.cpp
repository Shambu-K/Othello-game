#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>

class TIMER_T
{
    public:
    sf::Clock clock;
    sf::Time time;
    sf::Font font;
    sf::Text name;
    sf::Text digital_timer;
    sf::Vector2f position;
    sf::String name_string;
    std::string digital_string;
    sf::FloatRect digital_timer_boundaries;
    sf::FloatRect name_boundaries;
};

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

void define_button(sf::VertexArray& rectangle,sf::Vector2f position_rect,unsigned width, unsigned height)
{
    //sf::VertexArray rectangle(sf::Quads,4);
    rectangle[0].position = position_rect;
    rectangle[1].position = sf::Vector2f(position_rect.x + width,position_rect.y);
    rectangle[2].position = sf::Vector2f(position_rect.x + width,position_rect.y + height);
    rectangle[3].position = sf::Vector2f(position_rect.x ,position_rect.y + height);
    // define the color of the rectangle's points
    rectangle[0].color = sf::Color(200,200,200,100);
    rectangle[1].color = sf::Color(200,200,200,100);
    rectangle[2].color = sf::Color(49,245,250);
    rectangle[3].color = sf::Color(49,245,235);

};



void define_timer(TIMER_T& timer,sf::Font font,sf::String name,sf::Vector2f position)
{
    timer.font =font;
    timer.name_string=name;
    timer.position=position;

    timer.name.setFont(timer.font);
    timer.name.setString(timer.name_string);
    timer.name.setCharacterSize(12);
    timer.name.setFillColor(sf::Color::Black);
    timer.name.setPosition(timer.position);
    timer.name.setStyle(sf::Text::Bold | sf::Text::Underlined);
    timer.name_boundaries=timer.name.getGlobalBounds();

    timer.time =timer.clock.getElapsedTime();
    unsigned elapsed_time =300000- timer.time.asMilliseconds();
    unsigned millisecs =elapsed_time%1000;
    unsigned seconds = (elapsed_time/1000)%60;
    unsigned minutes = elapsed_time/60000;
    timer.digital_string = std::to_string(minutes);
    timer.digital_string.append(":");
    timer.digital_string.append(std::to_string(seconds));
    timer.digital_string.append(":");
    timer.digital_string.append(std::to_string(millisecs));

    timer.digital_timer.setFont(timer.font);
    timer.digital_timer.setString(timer.digital_string);
    timer.digital_timer.setCharacterSize(12);
    timer.digital_timer.setFillColor(sf::Color::Black);
    timer.digital_timer.setPosition(sf::Vector2f(timer.position.x,timer.position.y + timer.name_boundaries.height*1.2));
    timer.digital_timer_boundaries=timer.digital_timer.getGlobalBounds();

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

    sf::VertexArray rectangle(sf::Quads,4);
    sf::Vector2f rectangle_coordinates(3*No_moves_size.x/4,4*No_moves_size.y/5);
    unsigned rectangle_width=No_moves_size.x/5;
    unsigned rectangle_height=No_moves_size.x/10;
    define_button(rectangle,rectangle_coordinates,rectangle_width,rectangle_height);
    sf::FloatRect rectangle_boundaries;
    rectangle_boundaries.left=rectangle_coordinates.x;
    rectangle_boundaries.top=rectangle_coordinates.y;
    rectangle_boundaries.width=rectangle_width;
    rectangle_boundaries.height=rectangle_height;

    sf::Text text;
    text.setFont(font);
    text.setString("No legal moves possible");
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::Black);
    sf::FloatRect text_local_boundaries=text.getLocalBounds();
    text.setPosition((No_moves_size.x-text_local_boundaries.width)/3,(No_moves_size.y-text_local_boundaries.height)/3);
   // text.setPosition(No_moves_size.x/10,No_moves_size.y/10);
    

    sf::Text ok;
    ok.setFont(font);
    ok.setString("Ok");
    ok.setCharacterSize(12);
    ok.setFillColor(sf::Color::Black);
    sf::FloatRect ok_local_boundaries=ok.getLocalBounds();
    ok.setPosition(rectangle_boundaries.left+(rectangle_boundaries.width- ok_local_boundaries.width)/2,rectangle_boundaries.top+(rectangle_boundaries.height - ok_local_boundaries.height)/3);
    sf::FloatRect ok_boundaries= ok.getGlobalBounds();

    sf::RectangleShape ok_rectangle (sf::Vector2f(rectangle_boundaries.width,rectangle_boundaries.height));
    ok_rectangle.setPosition(sf::Vector2f(rectangle_boundaries.left,rectangle_boundaries.top));
    //ok_rectangle.setOutlineColor(sf::Color::Black);
    //ok_rectangle.setOutlineThickness(0.5);
    ok_rectangle.setFillColor(sf::Color(49,245,235));

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
        No_moves.draw(ok);
        No_moves.draw(text);
        No_moves.display();
    }
    
    
}
int main(){
        sf::RenderWindow window(sf::VideoMode(720,500),"Trial3");  
        //creating window
        window.setVerticalSyncEnabled(true);
        //setting the window
        sf::Vector2u window_size = window.getSize();

        auto image=sf::Image();
        if(!image.loadFromFile("icon2.png"))
        {
            return -1;
        }
        window.setIcon(image.getSize().x,image.getSize().y,image.getPixelsPtr());

        sf::Font font;
        if(!font.loadFromFile("arial.ttf"))
            return -1;
        sf::Text text;
        // select the font
        text.setFont(font); 
        // set the string to display
        text.setString("New game");
        // set the character size
        text.setCharacterSize(12); // in pixels, not points!
        // set the color
        text.setFillColor(sf::Color::Black);
        // set the text style
        text.setPosition(window_size.x /50,window_size.y /400);
        sf::FloatRect text_boundaries= text.getGlobalBounds();
       
        sf::RectangleShape rectangle(sf::Vector2f(text_boundaries.width*1.2,20.f));
        rectangle.setFillColor(sf::Color(49,245,235));
        rectangle.setPosition(sf::Vector2f(text_boundaries.left*0.5,0));

        sf::VertexArray main_menu(sf::Quads,4);
        define_button(main_menu,sf::Vector2f(0,0),480,20);

        TIMER_T white_timer;
        define_timer(white_timer,font,"white",sf::Vector2f(500.f,50.f)); 

        TIMER_T black_timer;
        define_timer(black_timer,font,"black",sf::Vector2f(600.f,50.f));

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
            "mygreen.png", "mywhite.png", "myblack.png", "mygray.png"
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
                    location.x=position.x*12/window_size.x;
                    location.y=(position.y-20)*8/window_size.y;
                    if(is_mouse_on_board(position))
                    {
                        level[location.x + location.y*8]=num_of_times%2 + 1;
                        num_of_times++;
                        turned=true;
                       
                    }
                    if((text_boundaries.left<position.x&&position.x<(text_boundaries.left+ text_boundaries.width))&&(text_boundaries.top<position.y&&position.y<(text_boundaries.top+ text_boundaries.height)))
                    {
                        for(unsigned i=0;i<64;i++)
                        {
                            level[i]=level_base[i];
                        }
                    }
                }
                //setting up command when left mouse button is clicked

                window.clear(sf::Color(220,220,220)); 
                print_all(names,sf::Vector2u(60.f,60.f),level,8,8,&window);
                //setting up the window
                if((text_boundaries.left<position.x&&position.x<(text_boundaries.left+ text_boundaries.width))&&(0<position.y&&position.y<(text_boundaries.top+ text_boundaries.height)))
                {
                    window.draw(rectangle);
                }
                if(num_of_times%2==0)
                {
                define_timer(white_timer,font,"white",sf::Vector2f(500.f,50.f));
                }

                if(num_of_times%2==1)
                {
                    define_timer(black_timer,font,"black",sf::Vector2f(600.f,50.f));
                }
                //num++;
                window.draw(main_menu);
                window.draw(text);
                window.draw(white_timer.name);
                window.draw(white_timer.digital_timer);
                window.draw(black_timer.name);
                window.draw(black_timer.digital_timer);
                window.display();      
                //displaying the window  
                /*if(num==1)
                {
                    no_legal_moves(position,&window,font);
                }*/
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&window.hasFocus()&&is_mouse_on_board(position)&&turned)
                {                    
                    while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {}                    
                    turned=false;
                }
        }     

}