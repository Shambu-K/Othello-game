#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>

class TIMER_T
{
    public:
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

void print_all(std::string* names, const int* tiles, unsigned int width, unsigned int height,sf::RenderWindow* window)
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
            sf::FloatRect sprite_bounds=sprite.getLocalBounds();
            texture.setSmooth(true);
            sprite.setPosition(i*sprite_bounds.width*1.f,20.f+j*sprite_bounds.height*1.f);
            window->draw(sprite);
            //adding the pieces to window here
        }
    }
}

bool is_mouse_on_board(sf::Vector2i position,sf::Image image,unsigned width,unsigned height)
{
    if((0<position.x)&&(position.x<(width*image.getSize().x))&&((20<position.y)&&(position.y<(height*image.getSize().y + 20))))
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

void pop_up(sf::String error_name,sf::Font font,sf::RenderWindow* window, sf::Time pop_up_time,unsigned pop_timelimit,float& vary)
{
    sf::Vector2u window_size=window->getSize();
    if(pop_up_time.asSeconds()<=0.5)
    {
        vary=pop_up_time.asSeconds();
    }
    else if (pop_up_time.asSeconds()>=pop_timelimit-0.5)
    {
        vary=3-pop_up_time.asSeconds();
    }
   
    sf::VertexArray pop_rectangle(sf::Quads,4);
    sf::Vector2f pop_rectangle_position(0,window_size.y*(20-vary*2)/20 );
    sf::Vector2u pop_rectangle_size(window_size.x,window_size.y*vary/10);
    define_button(pop_rectangle,pop_rectangle_position,pop_rectangle_size.x,pop_rectangle_size.y);

    
    sf::Text error_text;
    error_text.setFont(font);
    error_text.setString(error_name);
    error_text.setCharacterSize(12);
    error_text.setFillColor(sf::Color::Black);
    sf::FloatRect error_text_boundaries = error_text.getLocalBounds();
    sf::Vector2f error_text_position(pop_rectangle_position.x + (pop_rectangle_size.x-error_text_boundaries.width)/2,pop_rectangle_position.y + (pop_rectangle_size.y-error_text_boundaries.height)/2); 
    //sf::Vector2f error_text_position(10.f,500.f);
    error_text.setPosition(error_text_position);

    window->draw(pop_rectangle);
    if(vary>=0.4)window->draw(error_text);
}

void define_timer(TIMER_T& timer,sf::Clock clock,unsigned time_left,bool initiate,sf::Font font,sf::String name,sf::Vector2f position)
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

    timer.time =clock.getElapsedTime();
    unsigned elapsed_time =time_left- timer.time.asMilliseconds();
    if(initiate)elapsed_time=time_left;
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
    timer.digital_timer.setCharacterSize(13);
    timer.digital_timer.setFillColor(sf::Color::Black);
    timer.digital_timer.setPosition(sf::Vector2f(timer.position.x,timer.position.y + timer.name_boundaries.height*1.4));
    timer.digital_timer_boundaries=timer.digital_timer.getGlobalBounds();

}


int main(){
        sf::RenderWindow window(sf::VideoMode(720,600),"Trial3");  
        //creating window
        window.setVerticalSyncEnabled(true);
        //setting the window
        sf::Vector2u window_size = window.getSize();

        auto icon=sf::Image();
        if(!icon.loadFromFile("icon2.png"))
        {
            return -1;
        }
        window.setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());

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

        sf::Clock pop_up_clock;
        sf::Time pop_up_time;
        unsigned pop_up_timelimit=3;

        sf::Clock clock;
        unsigned white_time_left=300000;
        unsigned black_time_left=300000;
        bool initiate=true;
        bool run_time=false;
        sf::Vector2f white_position=sf::Vector2f(500.f,50.f);
        sf::Vector2f black_position=sf::Vector2f(600.f,50.f);

        TIMER_T white_timer;
        define_timer(white_timer,clock,white_time_left,initiate,font,"white",white_position); 

        TIMER_T black_timer;
        define_timer(black_timer,clock,black_time_left,initiate,font,"black",black_position);

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
        unsigned board_width=8;
        unsigned board_height=8;

        int num_of_times=0;
        int num=0;
        bool turned =false;
        bool pop=false;
        float pop_vary=0;
        std::string names[]={
            "mygreen.png", "mywhite.png", "myblack.png", "mygray.png"
        };
        //enter the names of the images of pieces

        auto image =sf::Image();
        if(!image.loadFromFile(names[1]))
            return -1;

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
                
                window.clear(sf::Color(220,220,220)); 
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&window.hasFocus())
                {
                    sf::Vector2u location;
                    location.x=position.x/image.getSize().x;
                    location.y=(position.y-20)/image.getSize().y;
                    if(is_mouse_on_board(position,image,board_width,board_height))
                    {
                        level[location.x + location.y*8]=num_of_times%2 + 1;
                        
                        sf::Time temp;
                        temp =clock.restart();
                        if(num_of_times%2==0)
                        {
                            white_time_left=white_time_left-temp.asMilliseconds();
                        }
                        else
                            black_time_left=black_time_left-temp.asMilliseconds();
                        
                        num_of_times++;
                        turned=true;
                    }
                    else if((text_boundaries.left<position.x&&position.x<(text_boundaries.left+ text_boundaries.width))&&(text_boundaries.top<position.y&&position.y<(text_boundaries.top+ text_boundaries.height)))
                    {
                        for(unsigned i=0;i<64;i++)
                        {
                            level[i]=level_base[i];
                            
                        }
                        white_time_left=300000;
                        black_time_left=300000;
                        define_timer(white_timer,clock,white_time_left,initiate,font,"white",white_position); 
                        define_timer(black_timer,clock,black_time_left,initiate,font,"black",black_position);
                        sf::Time temp=clock.restart();

                    }
                    else
                    {
                        pop=true;
                        sf::Time temp=pop_up_clock.restart();
                        pop_vary=0;
                    }
                }
                //setting up command when left mouse button is clicked

                
                print_all(names,level,8,8,&window);
                //setting up the window
                if((text_boundaries.left<position.x&&position.x<(text_boundaries.left+ text_boundaries.width))&&(0<position.y&&position.y<(text_boundaries.top+ text_boundaries.height)))
                {
                    window.draw(rectangle);
                }
                if(num_of_times%2==0)
                {
                define_timer(white_timer,clock,white_time_left,run_time,font,"white",white_position);
                }
                else
                {
                    define_timer(black_timer,clock,black_time_left,run_time,font,"black",black_position);
                }

                num++;
                pop_up_time=pop_up_clock.getElapsedTime();
                if(pop)
                {
                    pop_up("No legal moves",font,&window,pop_up_time,pop_up_timelimit,pop_vary);
                }
                if(pop_up_time.asSeconds()>pop_up_timelimit)
                pop=false;
                
                window.draw(main_menu);
                window.draw(text);
                window.draw(white_timer.name);
                window.draw(white_timer.digital_timer);
                window.draw(black_timer.name);
                window.draw(black_timer.digital_timer);
                window.display();      
                //displaying the window  
                
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&window.hasFocus()&&is_mouse_on_board(position,image,board_width,board_height)&&turned)
                {                    
                    while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {}                    
                    turned=false;
                }
                
        }     

}