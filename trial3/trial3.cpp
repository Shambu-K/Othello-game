#include<SFML/Graphics.hpp>
#include<iostream>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[i + j * width];

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
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
            sprite.setPosition(i*tileSize.x*1.f,j*tileSize.y*1.f);
            window->draw(sprite);
            //adding the pieces to window
        }
    }
}

int main(){
        sf::RenderWindow window(sf::VideoMode(480,480),"Trial3");  
        //creating window
        window.setVerticalSyncEnabled(true);
        //setting the window
         int level[] =
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
        //board configuration
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
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    int locationx=position.x/60;
                    int locationy=position.y/60;
                    if((0<position.x&&position.x<480)&&(0<position.y&&position.y<480)){
                    level[locationx + locationy*8]=1;}
                }
                //setting up command when left mouse button is clicked
                window.clear();
                print_all(names,sf::Vector2u(60.f,60.f),level,8,8,&window);
                //setting up the window
                window.display();      
                //displaying the window  
        }     

}