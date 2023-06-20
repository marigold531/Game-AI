#include "character/Boid.hpp"
#include "search_algorithm/AStar.hpp"
#include "search_algorithm/Dijkstra.hpp"

string getClosestVertex(Graph& graph, sf::Vector2f tilePos, std::vector<sf::RectangleShape *>& tiles) {
    std::string rtn = "";
    for (int i = 0; i < tiles.size(); i++) {
        sf::RectangleShape* tile = tiles[i];
        sf::FloatRect bounds = tile->getGlobalBounds();
        if (bounds.contains(tilePos)) {
            if (tile->getFillColor() == sf::Color(48, 74, 161)) {
                rtn = "wall";
            } else {
                rtn = std::to_string(i);
            }
        }
    }
    return rtn;
}

string getBoidVertex(Graph &graph, sf::Vector2f boidPos, std::vector<sf::RectangleShape *>& tiles) {
    std::string rtn = "";
    for(int i = 0; i < tiles.size(); i++) {
        sf::RectangleShape* tile = tiles[i];
        sf::FloatRect bounds = tile->getGlobalBounds();
        if(bounds.contains(boidPos)) {
            rtn = std::to_string(i);
        }
    }
    return rtn;
}   

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(640, 480), "CSC 484 HW3 PathFollowing", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    sf::Texture texture;
    texture.loadFromFile("resources/boid.png");

    Boid b = Boid(&window, "resources/boid.png", sf::Vector2f(16.f, 16.f));

    //Game Time
    sf::Clock gameTime;
    float lastTime = 0.f;

    int col = 20;
    int row = 15;
    int tileWidth = window.getSize().x / col;
    int tileHeight = window.getSize().y / row;
    //18x12
    
    std::vector<sf::RectangleShape *> tiles;
    for(int i = 0; i < col * row; i++){
        sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(tileWidth, tileHeight));
        shape->setPosition((i % col) * tileWidth, (i / col) * tileHeight);
        shape->setFillColor(sf::Color(155, 176, 160));
        tiles.push_back(shape);
    }
    
    //cout << tiles.size() << endl;

    //setting wall
    tiles.at(5)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(13)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(16)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(25)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(32)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(36)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(45)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(51)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(56)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(65)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(71)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(76)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(80)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(81)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(82)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(84)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(85)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(90)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(96)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(97)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(98)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(108)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(114)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(122)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(128)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(129)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(133)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(134)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(141)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(142)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(143)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(150)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(153)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(162)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(166)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(173)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(186)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(187)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(200)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(201)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(202)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(203)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(206)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(215)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(216)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(233)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(236)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(237)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(238)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(239)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(244)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(251)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(252)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(253)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(259)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(264)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(267)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(270)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(271)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(275)->setFillColor(sf::Color(48, 74, 161));
    //tiles.at(276)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(277)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(284)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(287)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(290)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(295)->setFillColor(sf::Color(48, 74, 161));
    tiles.at(297)->setFillColor(sf::Color(48, 74, 161));

    std::vector<sf::RectangleShape *> lines;
    for(int i = 1; i < col; i++){
        sf::RectangleShape* line = new sf::RectangleShape(sf::Vector2f(1, window.getSize().y));
        line->setPosition(i * tileWidth, 0);
        line->setFillColor(sf::Color(0,0,0));
        lines.push_back(line);
    }

    for(int i = 1; i < row; i++){
        sf::RectangleShape* line = new sf::RectangleShape(sf::Vector2f(window.getSize().x, 1));
        line->setPosition(0, i * tileHeight);
        line->setFillColor(sf::Color(0,0,0));
        lines.push_back(line);
    }

    //creating graph
    Graph tileGraph;
    
    for(int i = 0; i < row * col; i++) {
        if(tiles.at(i)->getFillColor() != sf::Color(48, 74, 161)) {
            float x = tiles.at(i)->getPosition().x + tileWidth / 2.0;
            float y = tiles.at(i)->getPosition().y + tileHeight / 2.0;
            string id = to_string(i);
            tileGraph.addCoordinates(id, x, y);
            int row_index = i / col;
            int col_index = i % col;

            bool hasWall = false;
            if(col_index > 0 && tiles.at(i - 1)->getFillColor() != sf::Color(48, 74, 161)) {
                string neighborId = to_string(i - 1);
                tileGraph.addEdge(id, neighborId, 1.0);
            }
            else {
                hasWall = true;
            }
            if(col_index < col - 1 && tiles.at(i + 1)->getFillColor() != sf::Color(48, 74, 161)) {
                string neighborId = to_string(i + 1);
                tileGraph.addEdge(id, neighborId, 1.0);
            }
            else {
                hasWall = true;
            }            
            if(row_index > 0 && tiles.at(i - col)->getFillColor() != sf::Color(48, 74, 161)) {
                string neighborId = to_string(i - col);
                tileGraph.addEdge(id, neighborId, 1.0);
            }
            else {
                hasWall = true;
            }
            if(row_index < row - 1 && tiles.at(i + col)->getFillColor() != sf::Color(48, 74, 161)) {
                string neighborId = to_string(i + col);
                tileGraph.addEdge(id, neighborId, 1.0);
            }
            else {
                hasWall = true;
            }

            if(row_index > 0 && col_index > 0 && tiles.at(i - col - 1)->getFillColor() != sf::Color(48, 74, 161) && !hasWall) {
                string neighborId = to_string(i - col - 1);
                tileGraph.addEdge(id, neighborId, 1.41);
            }
            if(row_index > 0 && col_index < col - 1 && tiles.at(i - col + 1)->getFillColor() != sf::Color(48, 74, 161) && !hasWall) {
                string neighborId = to_string(i - col + 1);
                tileGraph.addEdge(id, neighborId, 1.41);
            }
            if(row_index < row - 1 && col_index > 0 && tiles.at(i + col - 1)->getFillColor() != sf::Color(48, 74, 161) && !hasWall) {
                string neighborId = to_string(i + col - 1);
                tileGraph.addEdge(id, neighborId, 1.41);
            }
            if(row_index < row - 1 && col_index < col - 1 && tiles.at(i + col + 1)->getFillColor() != sf::Color(48, 74, 161) && !hasWall) {
                string neighborId = to_string(i + col + 1);
                tileGraph.addEdge(id, neighborId, 1.41);
            }
        }
    }

    // tileGraph.printGraph();

    Kinematic temp;
    temp.position = sf::Vector2f(0, 0);

    sf::Vector2i mousePos;
    
    AStar pathFinding;
    std::vector<std::string> path;
    std::vector<Kinematic *> pathKinematic;
    
    int pathIdx = 0;
    //cout << b.sprite.getPosition().x << endl;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    mousePos = sf::Mouse::getPosition(window);
                    
                    sf::Vector2f tilePos = window.mapPixelToCoords(mousePos);
                    std::string targetVertex = getClosestVertex(tileGraph, tilePos, tiles);
                    cout << "Tile pos" << tileGraph.coordinates.at(targetVertex).first << ", " << tileGraph.coordinates.at(targetVertex).second << endl << flush;
                    cout << "You click on tile: " << getClosestVertex(tileGraph, tilePos, tiles) << endl << flush;
                    cout << "Boid at tile " << getBoidVertex(tileGraph, b.getMyKinematic()->position, tiles) << endl << flush;
                    //A star
                }
                if(event.mouseButton.button == sf::Mouse::Right) {
                    pathIdx = 0;
                    path.clear();
                    pathKinematic.clear();
                    mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f tilePos = window.mapPixelToCoords(mousePos);
                    std::string boidVertex = getBoidVertex(tileGraph, b.getMyKinematic()->position, tiles);
                    std::string targetVertex = getClosestVertex(tileGraph, tilePos, tiles);
                    if(targetVertex != "wall") {
                        path = pathFinding.searchPath(tileGraph, boidVertex, targetVertex);
                        cout << "path: ";
                        for(int i = 0; i < path.size(); i++) {
                            cout << path.at(i) << " ";
                        }
                        cout << endl << flush;
                        if(path.size() > 0) {
                            for(int i = 0; i < path.size(); i++) {
                                if(tileGraph.coordinates.find(path.at(i)) != tileGraph.coordinates.end()) {
                                    sf::Vector2f position = {tileGraph.coordinates[path.at(i)].first, tileGraph.coordinates[path.at(i)].second};
                                    float degree = atan2(position.y - b.getMyKinematic()->position.y, position.x - b.getMyKinematic()->position.x);
                                    Kinematic* temp = new Kinematic(); 
                                    temp->position = position;
                                    temp->oreientation = degree;
                                    pathKinematic.emplace_back(temp);
                                }
                            }
                        }
                    }
                }
            }
        }

        float currentTime = gameTime.getElapsedTime().asSeconds();
        float elapsedTime = currentTime - lastTime;
        
        if(pathKinematic.size() > 0 ) {
            float distance = sqrt(pow(b.getMyKinematic()->position.x - pathKinematic.at(pathIdx)->position.x, 2) +
                        pow(b.getMyKinematic()->position.y - pathKinematic.at(pathIdx)->position.y, 2));
            if (distance < 1.0f) {
                if(pathIdx != pathKinematic.size() - 1) {
                    pathIdx++;
                    
                }
            }
            float degree = atan2(pathKinematic.at(pathIdx)->position.y - b.getMyKinematic()->position.y, pathKinematic.at(pathIdx)->position.x - b.getMyKinematic()->position.x);
            std::string boidVertex = getBoidVertex(tileGraph, b.getMyKinematic()->position, tiles);
            std::string targetVertex = getClosestVertex(tileGraph, pathKinematic.at(pathIdx)->position, tiles);
            if(boidVertex == targetVertex && pathIdx == pathKinematic.size() - 1) {
                degree = b.getMyKinematic()->oreientation;
            }
            //cout << pathIdx << ", " << pathKinematic.size() - 1 << endl;
            
            pathKinematic.at(pathIdx)->oreientation = degree;
            b.update(*pathKinematic.at(pathIdx), elapsedTime);
        }
        // else {
        //     b.update(*b.getMyKinematic(), elapsedTime);
        // }

        window.clear(sf::Color(150, 153, 146));


        //draw
        for (auto tile : tiles) {
            window.draw(*tile);
        }
        // for(auto line : lines) {
        //     window.draw(*line);
        // }
        b.draw();


        // for(auto const& vertex: tileGraph.coordinates) {
        //     float x = vertex.second.first;
        //     float y = vertex.second.second;
        //     sf::CircleShape circle(5.0);
        //     circle.setPosition(x - 5.0, y - 5.0);
        //     circle.setFillColor(sf::Color(255, 0, 0));
        //     window.draw(circle);
        // }

        // draw edges as lines
        // for(auto const& edge: tileGraph.edges) {
        //     string src = edge.first;
        //     for(auto const& dest: edge.second) {
        //         string destId = dest.first;
        //         float weight = dest.second;
        //         sf::Vertex line[] = {
        //             sf::Vertex(sf::Vector2f(tileGraph.coordinates[src].first, tileGraph.coordinates[src].second)),
        //             sf::Vertex(sf::Vector2f(tileGraph.coordinates[destId].first, tileGraph.coordinates[destId].second))
        //         };
        //         window.draw(line, 2, sf::Lines);
        //     }
        // }
        for(int i = 0; i < b.breadCrumbs->size(); i++) {
            b.breadCrumbs->at(i).draw(&window);
        }


        window.display();
        lastTime = currentTime;

    }
    for (auto tile : tiles) {
        delete tile;
    }
    for (auto line : lines) {
        delete line;
    }
}