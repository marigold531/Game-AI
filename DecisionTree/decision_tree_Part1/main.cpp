#include "character/Boid.hpp"
#include "search_algorithm/AStar.hpp"
#include "decision_tree/Node.hpp"

using namespace std;

float randomPos(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

int randomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

float distanceBetweenBoidAndItem(Boid& b, sf::CircleShape& item)
{
    float dx = b.getMyKinematic()->position.x - item.getPosition().x;
    float dy = b.getMyKinematic()->position.y - item.getPosition().y;
    return std::sqrt(dx * dx + dy * dy);
}

string getVertexBasedOnPosition(Graph &graph, sf::Vector2f boidPos, std::vector<sf::RectangleShape *>& tiles) {
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



bool isInBigRoom(Boid& boid, std::vector<sf::RectangleShape*>& tiles, Graph& graph, std::vector<sf::CircleShape>& allItems) {
    string boidCurrentV = getVertexBasedOnPosition(graph, boid.getMyKinematic()->position, tiles);
    if(tiles.at(stoi(boidCurrentV))->getFillColor() == sf::Color(103, 102, 148)) {
        return true;
    }
    return false;
}

bool isInBananaArea(Boid& boid, std::vector<sf::RectangleShape*>& tiles, Graph& graph, std::vector<sf::CircleShape>& allItems) {
    string boidCurrentV = getVertexBasedOnPosition(graph, boid.getMyKinematic()->position, tiles);
    if(tiles.at(stoi(boidCurrentV))->getFillColor() == sf::Color(232, 211, 63)) {
        return true;
    }
    return false;
}

bool isInWatermelonArea(Boid& boid, std::vector<sf::RectangleShape*>& tiles, Graph& graph, std::vector<sf::CircleShape>& allItems) {
    string boidCurrentV = getVertexBasedOnPosition(graph, boid.getMyKinematic()->position, tiles);
    if(tiles.at(stoi(boidCurrentV))->getFillColor() == sf::Color(213, 41, 65)) {
        return true;
    }
    return false;
}

bool isInFruitSaladArea(Boid& boid, std::vector<sf::RectangleShape*>& tiles, Graph& graph, std::vector<sf::CircleShape>& allItems) {
    string boidCurrentV = getVertexBasedOnPosition(graph, boid.getMyKinematic()->position, tiles);
    if(tiles.at(stoi(boidCurrentV))->getFillColor() == sf::Color(0, 79, 45)) {
        return true;
    }
    return false;
}

bool isInBathroomArea(Boid& boid, std::vector<sf::RectangleShape*>& tiles, Graph& graph, std::vector<sf::CircleShape>& allItems) {
    string boidCurrentV = getVertexBasedOnPosition(graph, boid.getMyKinematic()->position, tiles);
    if(tiles.at(stoi(boidCurrentV))->getFillColor() == sf::Color(17, 75, 95)) {
        return true;
    }
    return false;
}

bool isMonkeyFull(Boid& boid, std::vector<sf::RectangleShape*>& tiles, Graph& graph, std::vector<sf::CircleShape>& allItems) {
    if(boid.foodLevel >= 10) {
        return true;
    }
    return false;
}

bool canMonkeyStillRun(Boid& boid, std::vector<sf::RectangleShape*>& tiles, Graph& graph, std::vector<sf::CircleShape>& allItems) {
    if(boid.foodLevel > 4) {
        return true;
    }
    return false;
}

bool isToyNearBy(Boid& boid, std::vector<sf::RectangleShape*>& tiles, Graph& graph, std::vector<sf::CircleShape>& allItems) {
    for(auto i : allItems) {
        if(i.getFillColor() == sf::Color::Cyan && distanceBetweenBoidAndItem(boid, i) < 68) {
            return true;
        }
    }
    return false;
}

bool isBananaNearBy(Boid& boid, std::vector<sf::RectangleShape*>& tiles, Graph& graph, std::vector<sf::CircleShape>& allItems) {
    for(auto i : allItems) {
        if(i.getFillColor() == sf::Color(94, 91, 3) && distanceBetweenBoidAndItem(boid, i) < 68) {
            return true;
        }
    }
    return false; 
}

bool isWatermelonNearBy(Boid& boid, std::vector<sf::RectangleShape*>& tiles, Graph& graph, std::vector<sf::CircleShape>& allItems) {
    for(auto i : allItems) {
        if(i.getFillColor() == sf::Color(242, 194, 194) && distanceBetweenBoidAndItem(boid, i) < 68) {
            return true;
        }
    }
    return false;
}

bool isSaladNearBy(Boid& boid, std::vector<sf::RectangleShape*>& tiles, Graph& graph, std::vector<sf::CircleShape>& allItems) {
    for(auto i : allItems) {
        if(i.getFillColor() == sf::Color::Green && distanceBetweenBoidAndItem(boid, i) < 68) {
            return true;
        }
    }
    return false;
}

void processPath(const std::vector<std::string>& path, Boid& b, Graph& tileGraph, std::vector<Kinematic*>& pathKinematic) {
    if(path.size() > 0) {
        for(int i = 0; i < path.size(); i++) {
            if(tileGraph.coordinates.find(path.at(i)) != tileGraph.coordinates.end()) {
                sf::Vector2f position = {tileGraph.coordinates[path.at(i)].first, tileGraph.coordinates[path.at(i)].second};
                float degree = atan2(position.y - b.getMyKinematic()->position.y, position.x - b.getMyKinematic()->position.x);
                Kinematic* temp = new Kinematic(); 
                temp->position = position;
                temp->orientation = degree;
                pathKinematic.emplace_back(temp);
            }
        }
    }
}

int main()
{
    // ActionNode* actionNode1 = new ActionNode(1);
    // ActionNode* actionNode2 = new ActionNode(2);
    // ActionNode* actionNode3 = new ActionNode(3);
    // ActionNode* actionNode4 = new ActionNode(4);

    // ConditionNode* conditionNode2 = new ConditionNode(checky3, actionNode1, actionNode2);
    // ConditionNode* conditionNode3 = new ConditionNode(checky2, actionNode3, actionNode4);
    // ConditionNode* rootNode = new ConditionNode(checky, conditionNode2, conditionNode3);

    // int inputValue = 6;
    // int action = rootNode->evaluate(inputValue);
    // std::cout << "Action: " << action << std::endl;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(640, 480), "CSC 484 HW4", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    //Game Time
    sf::Clock gameTime;
    float lastTime = 0.f;

    int col = 40;
    int row = 30;
    float tileWidth = window.getSize().x / col;
    float tileHeight = window.getSize().y / row;

    sf::Texture texture;
    texture.loadFromFile("resources/boid.png");
    
    //boid
    Boid b = Boid(&window, "resources/boid.png", sf::Vector2f(30.f, 30.f));
   
    Arrive *arriveBehavior = new Arrive(2000, 257, 50, 0.001);
    Align *alignBehavior = new Align(0.001f, 4, 15, 10000);


    //wander
    float maxAcceleration = 200.f;
    float maxSpeed = 25.f;
    float targetRadiusArrive = 0.001f;
    float slowRadiusArrive = 50.f;

    float targetRadiusAlign = 0.001f;
    float slowRadiusAlign = 1.0f;
    float maxRotation = 3.0f;
    float maxAngularAcceleration = 5.0f;

    float wanderOffset = 190.f;
    float wanderRadius = 50.f;
    float wanderRate = 0.008667f;
    float wanderOrientation = 0.0f;

    Arrive *arriveBehaviorW = new Arrive(maxAcceleration, maxSpeed, slowRadiusArrive, targetRadiusArrive);
    Align *alignBehaviorW = new Align(targetRadiusAlign, slowRadiusAlign, maxRotation, maxAngularAcceleration);
    Wander wanderBehavior(wanderOffset, wanderRadius, wanderRate, wanderOrientation, arriveBehaviorW, alignBehaviorW);
    
    Kinematic target;

    std::vector<sf::RectangleShape *> tiles;
    for(int i = 0; i < col * row; i++){
        sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(tileWidth, tileHeight));
        shape->setPosition((i % col) * tileWidth, (i / col) * tileHeight);
        shape->setFillColor(sf::Color(155, 176, 160));
        tiles.push_back(shape);
    }
    //big room
    std::vector<sf::Vector2f> area1;
    //banana
    std::vector<sf::Vector2f> area2;
    //watermelon
    std::vector<sf::Vector2f> area3;
    //fruit salad
    std::vector<sf::Vector2f> area4;

    for(auto t : tiles) {
        //big room
        if(t->getPosition().x >= 0 && t->getPosition().x <= 440 && t->getPosition().y >= 0 && t->getPosition().y <= 150) {
            t->setFillColor(sf::Color(103, 102, 148));
            
        }
        else if(t->getPosition().x >= 0 && t->getPosition().x <= 180 && t->getPosition().y >= 150  && t->getPosition().y <= 360) {
            t->setFillColor(sf::Color(103, 102, 148));
            
        }
        //bathroom
        else if(t->getPosition().x >= 0 && t->getPosition().x <= 180 && t->getPosition().y >= 360 && t->getPosition().y <= 480) {
            t->setFillColor(sf::Color(17, 75, 95));
        }
        //banana
        else if(t->getPosition().x >= 180 && t->getPosition().x <= 390 && t->getPosition().y >= 150 && t->getPosition().y <= 480) {
            t->setFillColor(sf::Color(232, 211, 63));
            
        }
        //watermelon
        else if(t->getPosition().x >= 440 && t->getPosition().x <= 640 && t->getPosition().y >= 0 && t->getPosition().y <= 150) {
            t->setFillColor(sf::Color(213, 41, 65));
            
        }
        else if(t->getPosition().x >= 390 && t->getPosition().x <= 640 && t->getPosition().y >= 150 && t->getPosition().y <= 300) {
            t->setFillColor(sf::Color(213, 41, 65));
            
        }
        //fruit salad
        else {
            t->setFillColor(sf::Color(0, 79, 45));
            
        }
    }

    for(auto t : tiles) {
        if(t->getPosition().x == 0 || t->getPosition().y == 0 || (t->getPosition().x > 620 && t->getPosition().x < 640) || (t->getPosition().y > 460 && t->getPosition().y < 480)) {
            t->setFillColor(sf::Color(69, 69, 69));
        }
        if(t->getPosition().x == 432 && ((int)t->getPosition().y % 16 == 0) && t->getPosition().y <= 144){
             t->setFillColor(sf::Color(69, 69, 69));
        }
        if(t->getPosition().x >= 400 && t->getPosition().x <= 432 && t->getPosition().y == 160) {
             t->setFillColor(sf::Color(69, 69, 69));
        }
        if(t->getPosition().x == 400 && t->getPosition().y >= 176 && t->getPosition().y <= 208) {
             t->setFillColor(sf::Color(69, 69, 69));
        }
        if(t->getPosition().x >= 192 && t->getPosition().x <= 256 && t->getPosition().y == 160) {
            t->setFillColor(sf::Color(69, 69, 69));
        }
        if(t->getPosition().x >= 320 && t->getPosition().x <= 384 && t->getPosition().y == 160) {
            t->setFillColor(sf::Color(69, 69, 69));
        }
        if(t->getPosition().x == 400 && t->getPosition().y >= 256 && t->getPosition().y <= 336) {
            t->setFillColor(sf::Color(69, 69, 69));
        }
        if(t->getPosition().x == 400 && t->getPosition().y >= 384 && t->getPosition().y <= 448) {
            t->setFillColor(sf::Color(69, 69, 69));
        }
        if((t->getPosition().x == 16 && t->getPosition().y == 352)) {
            t->setFillColor(sf::Color(69, 69, 69));
        }
        if(t->getPosition().x >= 64 && t->getPosition().x <= 176 && t->getPosition().y == 352) {
            t->setFillColor(sf::Color(69, 69, 69));
        }
        if(t->getPosition().y >= 176 && t->getPosition().y <= 368 && t->getPosition().x == 192) {
            t->setFillColor(sf::Color(69, 69, 69));
        }
        if(t->getPosition().y >= 416 && t->getPosition().y <= 448 && t->getPosition().x == 192) {
            t->setFillColor(sf::Color(69, 69, 69));
        }
    }
    for(auto t : tiles) {
        if(t->getFillColor() == sf::Color(103, 102, 148)) {
            area1.emplace_back(t->getPosition());
        }
        else if(t->getFillColor() == sf::Color(232, 211, 63)) {
            area2.emplace_back(t->getPosition());
        }
        else if(t->getFillColor() == sf::Color(213, 41, 65)) {
            area3.emplace_back(t->getPosition());
        }
        else if(t->getFillColor() == sf::Color(0, 79, 45)) {
            area4.emplace_back(t->getPosition());
        }
    }
    std::vector<sf::RectangleShape *> lines;
    for(int i = 1; i < col; i++){
        sf::RectangleShape* line = new sf::RectangleShape(sf::Vector2f(1, window.getSize().y));
        line->setPosition(i * tileWidth, 0);
        line->setFillColor(sf::Color(69, 69, 69));
        lines.push_back(line);
    }

    for(int i = 1; i < row; i++){
        sf::RectangleShape* line = new sf::RectangleShape(sf::Vector2f(window.getSize().x, 1));
        line->setPosition(0, i * tileHeight);
        line->setFillColor(sf::Color(69, 69, 69));
        lines.push_back(line);
    }

    Graph tileGraph;
    
    for(int i = 0; i < row * col; i++) {
        if(tiles.at(i)->getFillColor() != sf::Color(69, 69, 69)) {
            float x = tiles.at(i)->getPosition().x + tileWidth / 2.0;
            float y = tiles.at(i)->getPosition().y + tileHeight / 2.0;
            string id = to_string(i);
            tileGraph.addCoordinates(id, x, y);
            int row_index = i / col;
            int col_index = i % col;

            bool hasWall = false;
            if(col_index > 0 && tiles.at(i - 1)->getFillColor() != sf::Color(69, 69, 69)) {
                string neighborId = to_string(i - 1);
                tileGraph.addEdge(id, neighborId, 1.0);
            }
            else {
                hasWall = true;
            }
            if(col_index < col - 1 && tiles.at(i + 1)->getFillColor() != sf::Color(69, 69, 69)) {
                string neighborId = to_string(i + 1);
                tileGraph.addEdge(id, neighborId, 1.0);
            }
            else {
                hasWall = true;
            }            
            if(row_index > 0 && tiles.at(i - col)->getFillColor() != sf::Color(69, 69, 69)) {
                string neighborId = to_string(i - col);
                tileGraph.addEdge(id, neighborId, 1.0);
            }
            else {
                hasWall = true;
            }
            if(row_index < row - 1 && tiles.at(i + col)->getFillColor() != sf::Color(69, 69, 69)) {
                string neighborId = to_string(i + col);
                tileGraph.addEdge(id, neighborId, 1.0);
            }
            else {
                hasWall = true;
            }

            if(row_index > 0 && col_index > 0 && tiles.at(i - col - 1)->getFillColor() != sf::Color(69, 69, 69) && !hasWall) {
                string neighborId = to_string(i - col - 1);
                tileGraph.addEdge(id, neighborId, 1.41);
            }
            if(row_index > 0 && col_index < col - 1 && tiles.at(i - col + 1)->getFillColor() != sf::Color(69, 69, 69) && !hasWall) {
                string neighborId = to_string(i - col + 1);
                tileGraph.addEdge(id, neighborId, 1.41);
            }
            if(row_index < row - 1 && col_index > 0 && tiles.at(i + col - 1)->getFillColor() != sf::Color(69, 69, 69) && !hasWall) {
                string neighborId = to_string(i + col - 1);
                tileGraph.addEdge(id, neighborId, 1.41);
            }
            if(row_index < row - 1 && col_index < col - 1 && tiles.at(i + col + 1)->getFillColor() != sf::Color(69, 69, 69) && !hasWall) {
                string neighborId = to_string(i + col + 1);
                tileGraph.addEdge(id, neighborId, 1.41);
            }
        }
    }
    std::vector<sf::CircleShape> allItems;
    for(int i = 0; i < 16; i++) {
        sf::CircleShape item(4.f);
        int randomNode;
        if(i < 5) { // toy
            item.setFillColor(sf::Color::Cyan);
            randomNode = randomInt(0, area1.size() - 1);
            item.setPosition(area1.at(randomNode));
        }
        else if(i >= 5 && i < 8) { // banana
            item.setFillColor(sf::Color(94, 91, 3));
            randomNode = randomInt(0, area2.size() - 1);
            item.setPosition(area2.at(randomNode));
        }
        else if(i >= 8 && i < 12) { // watermelon
            item.setFillColor(sf::Color(242, 194, 194));
            randomNode = randomInt(0, area3.size() - 1);
            item.setPosition(area3.at(randomNode));
        }
        else if(i >= 12 && i < 16) { // fruit salad
            item.setFillColor(sf::Color::Green);
            randomNode = randomInt(0, area4.size() - 1);
            item.setPosition(area4.at(randomNode));
        }
        allItems.push_back(item);
    }

    // ActionNode* actionNode1 = new ActionNode(1);
    // ActionNode* actionNode2 = new ActionNode(2);
    // ActionNode* actionNode3 = new ActionNode(3);
    // ActionNode* actionNode4 = new ActionNode(4);

    // ConditionNode* conditionNode2 = new ConditionNode(checky3, actionNode1, actionNode2);
    // ConditionNode* conditionNode3 = new ConditionNode(checky2, actionNode3, actionNode4);
    // ConditionNode* rootNode = new ConditionNode(checky, conditionNode2, conditionNode3);

    // int inputValue = 6;
    // int action = rootNode->evaluate(inputValue);
    // std::cout << "Action: " << action << std::endl;

    ActionNode* actionNode1 = new ActionNode(1); //pathfollow toy
    ActionNode* actionNode2 = new ActionNode(2); //wander
    ActionNode* actionNode3 = new ActionNode(3); // move to other area
    ActionNode* actionNode4 = new ActionNode(4); //

    
    ActionNode *wanderNode1 = new ActionNode(-1); // Wander (All Room) maybe no bathroom         right of bathroom Condition node
    //left of bathroom condition node
    ActionNode *wanderNode2 = new ActionNode(-2); // wander 
    ActionNode *pooNode = new ActionNode(1); // poo

    ActionNode *wanderNode3 = new ActionNode(-3);
    ActionNode *followFruitSalad = new ActionNode(2);

    ActionNode *wanderNode4 = new ActionNode(-4);
    ActionNode *followWatermelon = new ActionNode(3);

    ActionNode *wanderNode5 = new ActionNode(-5);
    ActionNode *followBanana = new ActionNode(4);

    ActionNode *moveToMainRoom = new ActionNode(5);

    ActionNode *moveToOtherArea = new ActionNode(6); // move to non main area
    ActionNode *moveToOtherArea2 = new ActionNode(6);

    ActionNode *moveToMainRoom2 = new ActionNode(5);
    ActionNode *followToy = new ActionNode(7);

    ActionNode *moveToBathroom = new ActionNode(8);
    ActionNode *moveToBathroom2 = new ActionNode(8);
    ActionNode *moveToBathroom3 = new ActionNode(8);
    // 
    // ConditionNode* inBathRoomCond = new ConditionNode(isInBathroomArea, checkFullHunger1, wanderNode1);

    ConditionNode* checkNearFruitSalad = new ConditionNode(isSaladNearBy, followFruitSalad, wanderNode2);
    ConditionNode* monkeyFullInSaladArea = new ConditionNode(isMonkeyFull, moveToBathroom, checkNearFruitSalad);
    ConditionNode* inFruitSaladAreaCond = new ConditionNode(isInFruitSaladArea, monkeyFullInSaladArea, wanderNode1);

    ConditionNode* checkNearWatermelon = new ConditionNode(isWatermelonNearBy, followWatermelon, wanderNode3);
    ConditionNode* monkeyFullInWatermelonArea = new ConditionNode(isMonkeyFull, moveToBathroom2, checkNearWatermelon);
    ConditionNode* inWatermelonAreaCond = new ConditionNode(isInWatermelonArea, monkeyFullInWatermelonArea, inFruitSaladAreaCond);

    ConditionNode* checkNearBanana = new ConditionNode(isBananaNearBy, followBanana, wanderNode4);
    ConditionNode* monkeyFullInBananaArea = new ConditionNode(isMonkeyFull, moveToBathroom3, checkNearBanana);
    ConditionNode* inBananaAreaCond = new ConditionNode(isInBananaArea, monkeyFullInBananaArea, inWatermelonAreaCond);

    ConditionNode* checkFullHunger1 = new ConditionNode(isMonkeyFull, pooNode, moveToMainRoom);
    ConditionNode* inBathRoomCond = new ConditionNode(isInBathroomArea, checkFullHunger1, inBananaAreaCond);

    ConditionNode* checkNearToy = new ConditionNode(isToyNearBy, followToy, moveToMainRoom2);

    ConditionNode* checkMonkeyCanRunNode = new ConditionNode(canMonkeyStillRun, checkNearToy, moveToOtherArea);

    ConditionNode* rootNodeMonkey = new ConditionNode(isInBigRoom, checkMonkeyCanRunNode, inBathRoomCond);

    
    AStar pathFinding;
    sf::Vector2i mousePos;
    std::vector<std::string> path;
    std::vector<Kinematic *> pathKinematic;
    int pathIdx = 1;
    //cout << getVertexBasedOnPosition(tileGraph, b.getMyKinematic()->position, tiles) << endl;
    bool goWander = true;
    bool goPath = false;
    bool goToMain = true;
    bool bathroomPath = true;
    bool moveToOtherRoom = true;

    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("resources/ARIAL.TTF")) {
        std::cerr << "Error loading font" << std::endl;
        return 1;
    }
    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(10.0f, 0.0f));
    text.setString(to_string(b.foodLevel));

    //bool wanderPathDone = true;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, tiles.size() - 1);

    while (window.isOpen()) {
         sf::Event event;
         while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
         }

        float currentTime = gameTime.getElapsedTime().asSeconds();
        float elapsedTime = currentTime - lastTime;


        int action = rootNodeMonkey->evaluate(b, tiles, tileGraph, allItems);

        if(action <= 0) {
            std::cout << "Monkey wandering "  << action << std::endl << flush;
            if(goWander) {
                moveToOtherRoom = true;
                std::string randomVertex;
                std::string boidVertex = getVertexBasedOnPosition(tileGraph, b.getMyKinematic()->position, tiles);
                while(true) {

                    int vertexId = dist(gen);
                    if(tiles.at(vertexId)->getFillColor() != sf::Color(69, 69, 69)) {
                        randomVertex = std::to_string(vertexId);
                        break;
                    }

                }
                pathIdx = 1;
                path.clear();
                pathKinematic.clear();
                path = pathFinding.searchPath(tileGraph, boidVertex, randomVertex);
                cout << "wander path: ";
                for(int i = 0; i < path.size(); i++) {
                    cout << path.at(i) << " ";
                }
                cout << endl << flush;
                processPath(path, b, tileGraph, pathKinematic);
                goWander = false;
                //wanderPathDone = false;
            }
        }
        else if(action == 1) {
            std::cout << "Monkey pooping"  << std::endl << flush;
            b.foodLevel -= 1;
                        // goWander = true;
            // moveToOtherRoom = true;
        }
        else if(action == 2) {
            std::cout << "Monkey go for salad"  << std::endl << flush;

            goWander = true;
            moveToOtherRoom = true;

            bool foundSalad = false;
            sf::Vector2f nearestToy;
            for(auto &item : allItems) {
                if(item.getFillColor() == sf::Color::Green && distanceBetweenBoidAndItem(b, item) < 68) {
                    nearestToy = item.getPosition();
                    foundSalad = true;
                    break;
                }
            }
            if(foundSalad) {
                //cout << getVertexBasedOnPosition(tileGraph, b.sprite.getPosition(), tiles) << endl << flush;
                //cout << getVertexBasedOnPosition(tileGraph, nearestToy, tiles) << endl << flush;
                pathIdx = 1;
                path.clear();
                pathKinematic.clear();
                path = pathFinding.searchPath(tileGraph, getVertexBasedOnPosition(tileGraph, b.sprite.getPosition(), tiles), getVertexBasedOnPosition(tileGraph, nearestToy, tiles));
                processPath(path, b, tileGraph, pathKinematic);
            }
        }
        else if(action == 3) {
            std::cout << "Monkey go for watermelon" << std::endl << flush;
            
            goWander = true;
            moveToOtherRoom = true;

            bool foundMelon = false;
            sf::Vector2f nearestToy;
            for(auto &item : allItems) {
                if(item.getFillColor() == sf::Color(242, 194, 194) && distanceBetweenBoidAndItem(b, item) < 68) {
                    nearestToy = item.getPosition();
                    foundMelon = true;
                    break;
                }
            }
            if(foundMelon) {
                pathIdx = 1;
                path.clear();
                pathKinematic.clear();
                path = pathFinding.searchPath(tileGraph, getVertexBasedOnPosition(tileGraph, b.sprite.getPosition(), tiles), getVertexBasedOnPosition(tileGraph, nearestToy, tiles));
                processPath(path, b, tileGraph, pathKinematic);
            }
        }
        else if(action == 4) {
            std::cout << "Monkey go for banana"  << std::endl << flush;

            goWander = true;
            moveToOtherRoom = true;

            bool foundBanana = false;
            sf::Vector2f nearestToy;
            for(auto &item : allItems) {
                if(item.getFillColor() == sf::Color(94, 91, 3) && distanceBetweenBoidAndItem(b, item) < 68) {
                    nearestToy = item.getPosition();
                    foundBanana = true;
                    break;
                }
            }
            if(foundBanana) {
                pathIdx = 1;
                path.clear();
                pathKinematic.clear();
                path = pathFinding.searchPath(tileGraph, getVertexBasedOnPosition(tileGraph, b.sprite.getPosition(), tiles), getVertexBasedOnPosition(tileGraph, nearestToy, tiles));
                processPath(path, b, tileGraph, pathKinematic);
            }
        }
        else if(action == 5) {
            std::cout << "Monkey back to main room"  << std::endl << flush;
            if(goToMain) {
                pathIdx = 1;
                path.clear();
                pathKinematic.clear();
                std::uniform_int_distribution<> mainRoomRNG(0, area1.size() - 1);
                string randomVertex = getVertexBasedOnPosition(tileGraph, area1.at(mainRoomRNG(gen)), tiles);

                path = pathFinding.searchPath(tileGraph, getVertexBasedOnPosition(tileGraph, b.sprite.getPosition(), tiles), randomVertex);
                processPath(path, b, tileGraph, pathKinematic);
                goToMain = false;
            }
        }
        else if(action == 6) {
            std::cout << "Monkey move to other areas" << std::endl << flush;

            goWander = true;
            if(moveToOtherRoom) {
                pathIdx = 1;
                path.clear();
                pathKinematic.clear();
                string randomVertex;
                string boidVertex = getVertexBasedOnPosition(tileGraph, b.getMyKinematic()->position, tiles);
                std::uniform_int_distribution<> dist2(2, 4);
                int randomArea = dist2(gen);
                sf::Vector2f randomPos;
                if(randomArea == 2) {
                    std::uniform_int_distribution<> yellow(0, area2.size() - 1);
                    randomVertex = getVertexBasedOnPosition(tileGraph, area2.at(yellow(gen)), tiles);
                } else if(randomArea == 3) {
                    std::uniform_int_distribution<> red(0, area3.size() - 1);
                    randomVertex = getVertexBasedOnPosition(tileGraph, area2.at(red(gen)), tiles);
                } else if(randomArea == 4) {
                    std::uniform_int_distribution<> green(0, area4.size() - 1);
                    randomVertex = getVertexBasedOnPosition(tileGraph, area2.at(green(gen)), tiles);
                }

                cout << "moving to room: " << randomArea << " with vertex: " << randomVertex << endl;
                path = pathFinding.searchPath(tileGraph, boidVertex, randomVertex);
                processPath(path, b, tileGraph, pathKinematic);
                moveToOtherRoom = false;
            }
            
        }
        else if(action == 7) {
            std::cout << "Monkey go for toy "  << std::endl << flush;

            goWander = true;
            //wanderPathDone = true;
            bool foundToy = false;
            sf::Vector2f nearestToy;
            for(auto &item : allItems) {
                if(item.getFillColor() == sf::Color::Cyan && distanceBetweenBoidAndItem(b, item) < 68) {
                    nearestToy = item.getPosition();
                    foundToy = true;
                    break;
                }
            }
            if(foundToy) {
                pathIdx = 1;
                path.clear();
                pathKinematic.clear();
                path = pathFinding.searchPath(tileGraph, getVertexBasedOnPosition(tileGraph, b.sprite.getPosition(), tiles), getVertexBasedOnPosition(tileGraph, nearestToy, tiles));
                processPath(path, b, tileGraph, pathKinematic);
            }
        }
        else if(action == 8) {
            std::cout << "Monkey move to bathroom" << endl;
            goWander = true;
            moveToOtherRoom = true;
            if(bathroomPath) {
                pathIdx = 1;
                path.clear();
                pathKinematic.clear();
                path = pathFinding.searchPath(tileGraph, getVertexBasedOnPosition(tileGraph, b.sprite.getPosition(), tiles), getVertexBasedOnPosition(tileGraph, sf::Vector2f(90, 300), tiles));
                processPath(path, b, tileGraph, pathKinematic);
                bathroomPath = false;
            }

            // std::cout << "Monkey move to other room"  << std::endl << flush;


        }
        if(pathKinematic.size() <= 1) {
            goWander = true;
            moveToOtherRoom = true;
            goToMain = true;
            bathroomPath = true;
            //continue;
        }
        if(pathKinematic.size() > 1) {
            float degree = atan2(pathKinematic.at(pathIdx)->position.y - b.getMyKinematic()->position.y, pathKinematic.at(pathIdx)->position.x - b.getMyKinematic()->position.x);
            std::string boidVertex = getVertexBasedOnPosition(tileGraph, b.getMyKinematic()->position, tiles);
            std::string targetVertex = getVertexBasedOnPosition(tileGraph, pathKinematic.at(pathIdx)->position, tiles);
            if(boidVertex == targetVertex && pathIdx == pathKinematic.size() - 1) {
                degree = b.getMyKinematic()->orientation;
                if(!goWander) {
                    goWander = true;
                }
                if(!moveToOtherRoom) {
                    moveToOtherRoom = true;
                }
                if(!goToMain) {
                    goToMain = true;
                }
                if(!bathroomPath) {
                    bathroomPath = true;
                }
                //wanderPathDone = true;
                
            }
            pathKinematic.at(pathIdx)->orientation = degree;
            float distance = sqrt(pow(b.getMyKinematic()->position.x - pathKinematic.at(pathIdx)->position.x, 2) + pow(b.getMyKinematic()->position.y - pathKinematic.at(pathIdx)->position.y, 2));
            if (distance <= 5.0f) {
                if(pathIdx != pathKinematic.size() - 1) {
                    pathIdx++;
                }
            }
            if(pathIdx < pathKinematic.size() - 1) {
                arriveBehavior->targetRadius = 5.f;
            }
            else {
                arriveBehavior->targetRadius = targetRadiusArrive;
            }
            SteeringOutput temp;
            temp.linearAcceleration = arriveBehavior->calculateAcceleration(*b.getMyKinematic(), *pathKinematic.at(pathIdx)).linearAcceleration;
            temp.angularAcceleration = alignBehavior->calculateAcceleration(*b.getMyKinematic(), *pathKinematic.at(pathIdx)).angularAcceleration;
            b.update(temp, elapsedTime);
        }

        for(auto& i : allItems) {
            if(i.getFillColor() == sf::Color::Cyan) {
                string toyVertex = getVertexBasedOnPosition(tileGraph, i.getPosition(), tiles);
                string boidVertex = getVertexBasedOnPosition(tileGraph, b.getMyKinematic()->position, tiles);
                if(toyVertex == boidVertex) {
                    int randomNode = randomInt(0, area1.size() - 1);
                    i.setPosition(area1.at(randomNode));
                    b.foodLevel -= 1;
                }
            }
            else if(i.getFillColor() == sf::Color(94, 91, 3)) {
                string toyVertex = getVertexBasedOnPosition(tileGraph, i.getPosition(), tiles);
                string boidVertex = getVertexBasedOnPosition(tileGraph, b.getMyKinematic()->position, tiles);
                if(toyVertex == boidVertex) {
                    int randomNode = randomInt(0, area2.size() - 1);
                    i.setPosition(area2.at(randomNode));
                    b.foodLevel += 1;
                }
            }
            else if(i.getFillColor() == sf::Color(242, 194, 194)) {
                string toyVertex = getVertexBasedOnPosition(tileGraph, i.getPosition(), tiles);
                string boidVertex = getVertexBasedOnPosition(tileGraph, b.getMyKinematic()->position, tiles);
                if(toyVertex == boidVertex) {
                    int randomNode = randomInt(0, area3.size() - 1);
                    i.setPosition(area3.at(randomNode));
                    b.foodLevel += 1;
                }
            }
            else if(i.getFillColor() == sf::Color::Green) {
                string toyVertex = getVertexBasedOnPosition(tileGraph, i.getPosition(), tiles);
                string boidVertex = getVertexBasedOnPosition(tileGraph, b.getMyKinematic()->position, tiles);
                if(toyVertex == boidVertex) {
                    int randomNode = randomInt(0, area4.size() - 1);
                    i.setPosition(area4.at(randomNode));
                    b.foodLevel += 1;
                }
            }
        }

        cout << "size: " << pathKinematic.size() << " GoWander: " << goWander << " moveToOtherRoom: " << moveToOtherRoom << " goToMain: " << goToMain << " bathroomPath: " << bathroomPath<< endl;
        text.setString("Food Level: " + to_string(b.foodLevel));
        
        window.clear(sf::Color(150, 153, 146));
        for (auto tile : tiles) {
            window.draw(*tile);
        }

        for(auto item : allItems) {
            window.draw(item);
        }

        b.draw();
        window.draw(text);
       
        window.display();
        lastTime = currentTime;
    }
    // delete actionNode1;
    // delete actionNode2;
    // delete rootNode;
}