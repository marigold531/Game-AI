#include "decision_tree/BehaviorTree.hpp"
#include "character/Boid.hpp"
#include "search_algorithm/AStar.hpp"
#include <fstream>
#include <sstream>

AStar pathFinding;
Graph tileGraph;

struct MonsterState {
    bool near_monkey;
    bool collide_with_monkey;
    bool stamina_bad;
    bool near_fruit;
    string action;
};

MonsterState monsterState;

int randomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
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

bool nearMonkeyCondition(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems) {
    for(auto &monkey: monkeys) {
        float dx = monkey.getMyKinematic()->position.x - monster.getMyKinematic()->position.x;
        float dy = monkey.getMyKinematic()->position.y - monster.getMyKinematic()->position.y;
        if(std::sqrt(dx * dx + dy * dy) <= 70) {
            return true;
        }
    }
    return false;
}

bool decreaseStaminaAction(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems) {
    monster.stamina -= (1.f/15.f);
    printf("decrease stamina\n");
    monsterState.action = "decrease stamina";
    return true;
}

bool followMonkeyAction(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems) {
    
    for(auto &monkey: monkeys) {
        float dx = monkey.getMyKinematic()->position.x - monster.getMyKinematic()->position.x;
        float dy = monkey.getMyKinematic()->position.y - monster.getMyKinematic()->position.y;
        if(std::sqrt(dx * dx + dy * dy) <= 70) {
            monster.pathIdx = 1;
            monster.path.clear();
            monster.pathKinematic.clear();
            string monsterVertex = getVertexBasedOnPosition(tileGraph, monster.getMyKinematic()->position, tiles);
            string monkeyVertex = getVertexBasedOnPosition(tileGraph, monkey.getMyKinematic()->position, tiles);
            monster.path = pathFinding.searchPath(tileGraph, monsterVertex, monkeyVertex);
            processPath(monster.path, monster, tileGraph, monster.pathKinematic);
        }
    }
    printf("following monkey\n");
    monsterState.action = "follow monkey";
    return true;
}

bool collideWithMonkeyCondition(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems) {
    for(auto &monkey : monkeys) {
        string monkeyVertex = getVertexBasedOnPosition(tileGraph, monkey.getMyKinematic()->position, tiles);
        string monsterVertex = getVertexBasedOnPosition(tileGraph, monster.getMyKinematic()->position, tiles);
        if(monsterVertex == monkeyVertex) {
            return true;
        }
    }
    return false;
}

bool attackMonkeyAction(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems) {
    for(auto &monkey : monkeys) {
        monkey.resetPosition();
    }
    monster.resetPosition();
    printf("beat'em up\n");
    monsterState.action = "attack";
    return true;
}

bool checkStaminaBad(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems) {
    if(monster.stamina < 4) {
        return true;
    }
    return false;
}

bool checkNearFruitCondition(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems) {
    for(auto &item : allItems) {
        float dx = item.getPosition().x - monster.getMyKinematic()->position.x;
        float dy = item.getPosition().y - monster.getMyKinematic()->position.y;
        if(std::sqrt(dx * dx + dy * dy) <= 100) {
            return true;
        }
    }
    return false;
}

bool followFruitAction(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems) {
    // for(auto monkey: monkeys) {
    //     float dx = monkey.getMyKinematic()->position.x - monster.getMyKinematic()->position.x;
    //     float dy = monkey.getMyKinematic()->position.y - monster.getMyKinematic()->position.y;
    //     if(std::sqrt(dx * dx + dy * dy) <= 70) {
    //         monster.pathIdx = 1;
    //         monster.path.clear();
    //         monster.pathKinematic.clear();
    //         string monsterVertex = getVertexBasedOnPosition(tileGraph, monster.getMyKinematic()->position, tiles);
    //         string monkeyVertex = getVertexBasedOnPosition(tileGraph, monkey.getMyKinematic()->position, tiles);
    //         monster.path = pathFinding.searchPath(tileGraph, monsterVertex, monkeyVertex);
    //     }
    // }
    for(auto &item : allItems) {
        float dx = monster.getMyKinematic()->position.x - item.getPosition().x;
        float dy = monster.getMyKinematic()->position.y - item.getPosition().y;
        if(std::sqrt(dx * dx + dy * dy) <= 100) {
            if(monster.canCreateFruitPath) {
                monster.pathIdx = 1;
                monster.path.clear();
                monster.pathKinematic.clear();
                string monsterVertex = getVertexBasedOnPosition(tileGraph, monster.getMyKinematic()->position, tiles);
                string fruitVertex = getVertexBasedOnPosition(tileGraph, item.getPosition(), tiles);
                monster.path = pathFinding.searchPath(tileGraph, monsterVertex, fruitVertex);
                processPath(monster.path, monster, tileGraph, monster.pathKinematic);
                monster.canCreateFruitPath = false;
            }
            
        }
    }
    printf("gonna go follow fruit\n");
    monsterState.action = "follow fruit";
    return true;
}

bool wanderAction(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems) {
    if(monster.canCreateWanderPath) {
        string randomVertex; 
        string monsterVertex = getVertexBasedOnPosition(tileGraph, monster.getMyKinematic()->position, tiles);
        while(true) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(0, tiles.size() - 1);
            int vertexId = dist(gen);
            if(tiles.at(vertexId)->getFillColor() != sf::Color(69, 69, 69)) {
                randomVertex = std::to_string(vertexId);
                break;
            }
        }
        monster.pathIdx = 1;
        monster.path.clear();
        monster.pathKinematic.clear();
        //string monsterVertex = getVertexBasedOnPosition(tileGraph, monster.getMyKinematic()->position, tiles);
        monster.path = pathFinding.searchPath(tileGraph, monsterVertex, randomVertex);
        processPath(monster.path, monster, tileGraph, monster.pathKinematic);
        
        monster.canCreateWanderPath = false;
    }
    printf("nothing to do gonna wander\n");
    monsterState.action = "wander";
    return true;
}


void updateMonsterState(Boid& monster, std::vector<Boid>& monkeys, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems, MonsterState& state) {
    state.near_monkey = nearMonkeyCondition(monkeys, monster, tiles, allItems);
    state.collide_with_monkey = collideWithMonkeyCondition(monkeys, monster, tiles, allItems);
    state.stamina_bad = checkStaminaBad(monkeys, monster, tiles, allItems);
    state.near_fruit = checkNearFruitCondition(monkeys, monster, tiles, allItems);
    // The action will be updated when the behavior tree runs and executes an action node
}
using namespace std;

int main() {

    ActionNode *wanderActionNode = new ActionNode(wanderAction);
    ConditionNode *checkGoodStamina = new ConditionNode(checkStaminaBad);
    ActionNode *followFruitActionNode = new ActionNode(followFruitAction);
    ConditionNode *checkNearFruitNode = new ConditionNode(checkNearFruitCondition);
    vector<TreeNode*> sequenceFruitNodes = {checkGoodStamina, checkNearFruitNode, followFruitActionNode};
    SequenceNode *sequenceFruitNode = new SequenceNode(sequenceFruitNodes);

    ConditionNode *checkAtCharacterNode = new ConditionNode(collideWithMonkeyCondition);
    ConditionNode *checkStaminaBadNode = new ConditionNode(checkStaminaBad);
    InverterNode *invertStaminaCheckNode = new InverterNode(checkStaminaBadNode);
    ActionNode *attackMonkeyNode = new ActionNode(attackMonkeyAction);
    vector<TreeNode*> sequenceAttackNodes = {checkAtCharacterNode, invertStaminaCheckNode, attackMonkeyNode};
    SequenceNode *sequenceAttackNode = new SequenceNode(sequenceAttackNodes);

    ActionNode *followMonkeyNode = new ActionNode(followMonkeyAction);
    ActionNode *decreaseStaminaNode = new ActionNode(decreaseStaminaAction);
    ConditionNode *checkNearMonkeyNode = new ConditionNode(nearMonkeyCondition);
    ConditionNode *checkStaminaBadNode2 = new ConditionNode(checkStaminaBad);
    InverterNode *invertStaminaCheckNode2 = new InverterNode(checkStaminaBadNode);
    vector<TreeNode *> sequenceFollowMonkeyNodes = {invertStaminaCheckNode2, checkNearMonkeyNode, decreaseStaminaNode, followMonkeyNode};
    SequenceNode *sequenceFollowMonkeyNode = new SequenceNode(sequenceFollowMonkeyNodes);
    vector<TreeNode *> selectorNodes = {sequenceAttackNode, sequenceFollowMonkeyNode, sequenceFruitNode, wanderActionNode};
    SelectorNode *selectActionNode = new SelectorNode(selectorNodes);




    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(640, 480), "CSC 484 HW4", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    //Game Time
    sf::Clock gameTime;
    float lastTime = 0.f;

    sf::Texture texture;
    texture.loadFromFile("resources/boid.png");

    Arrive *arriveBehavior = new Arrive(2000, 257, 50, 0.001);
    Align *alignBehavior = new Align(0.001f, 4, 15, 10000);

    //Room setup
    int col = 40;
    int row = 30;
    float tileWidth = window.getSize().x / col;
    float tileHeight = window.getSize().y / row;

    //big room
    std::vector<sf::Vector2f> area1;
    //banana
    std::vector<sf::Vector2f> area2;
    //watermelon
    std::vector<sf::Vector2f> area3;
    //fruit salad
    std::vector<sf::Vector2f> area4;

    std::vector<sf::RectangleShape *> tiles;

    for(int i = 0; i < col * row; i++){
        sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(tileWidth, tileHeight));
        shape->setPosition((i % col) * tileWidth, (i / col) * tileHeight);
        shape->setFillColor(sf::Color(155, 176, 160));
        tiles.push_back(shape);
    }
    for(auto &t : tiles) {
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
    //setting walls
    for(auto &t : tiles) {
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
    for(auto &t : tiles) {
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

    //visual assist
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

    //Graph Vertex setup
    
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

    //items(food) setup
    // std::vector<sf::CircleShape> allItems;
    // for(int i = 0; i < 14; i++) {
    //     sf::CircleShape item(4.f);
    //     int randomNode;
    //     if(i < 5) { // Grapes
    //         item.setFillColor(sf::Color(255,0,255));
    //         randomNode = randomInt(0, area1.size() - 1);
    //         item.setPosition(area1.at(randomNode));
    //     }
    //     else if(i >= 5 && i < 8) { // banana
    //         item.setFillColor(sf::Color(94, 91, 3));
    //         randomNode = randomInt(0, area2.size() - 1);
    //         item.setPosition(area2.at(randomNode));
    //     }
    //     else if(i >= 8 && i < 11) { // watermelon
    //         item.setFillColor(sf::Color(242, 194, 194));
    //         randomNode = randomInt(0, area3.size() - 1);
    //         item.setPosition(area3.at(randomNode));
    //     }
    //     else if(i >= 11 && i < 14) { // fruit salad
    //         item.setFillColor(sf::Color::Green);
    //         randomNode = randomInt(0, area4.size() - 1);
    //         item.setPosition(area4.at(randomNode));
    //     }
    //     allItems.push_back(item);
    // }
    std::vector<sf::CircleShape> allItems;
    for(int i = 0; i < 8; i++) {
        sf::CircleShape item(4.f);
        int randomNode;
        if(i < 3) { // Grapes
            item.setFillColor(sf::Color(255,0,255));
            randomNode = randomInt(0, area1.size() - 1);
            item.setPosition(area1.at(randomNode));
        }
        else if(i >= 3 && i < 5) { // banana
            item.setFillColor(sf::Color(94, 91, 3));
            randomNode = randomInt(0, area2.size() - 1);
            item.setPosition(area2.at(randomNode));
        }
        else if(i >= 5 && i < 6) { // watermelon
            item.setFillColor(sf::Color(242, 194, 194));
            randomNode = randomInt(0, area3.size() - 1);
            item.setPosition(area3.at(randomNode));
        }
        else if(i >= 6 && i < 8) { // fruit salad
            item.setFillColor(sf::Color::Green);
            randomNode = randomInt(0, area4.size() - 1);
            item.setPosition(area4.at(randomNode));
        }
        allItems.push_back(item);
    }
    //character setup
    //monkey
    Boid monkey1 = Boid(&window, "resources/MankeyJungle_Walk_strip6.png", sf::Vector2f(30.f, 30.f), 1);
    Boid monkey2 = Boid(&window, "resources/MankeyJungle_Walk_strip6.png", sf::Vector2f(100.f, 400.f), 1);
    std::vector<Boid> monkeys = {monkey1, monkey2};

    Boid monster = Boid(&window, "resources/Flight.png", sf::Vector2f(181, 30), 2);

    
    
    //Game loop
    while (window.isOpen()) {
        
        updateMonsterState(monster, monkeys, tiles, allItems, monsterState);
        bool result = selectActionNode->evaluate(monkeys, monster, tiles, allItems);
        std::ofstream outputFile("monster_state_data.txt", std::ios::app);

        if (outputFile.is_open()) {
            outputFile << monsterState.near_monkey << "," << monsterState.collide_with_monkey << ","
                    << monsterState.stamina_bad << "," << monsterState.near_fruit << ","
                    << monsterState.action << std::endl;
            outputFile.close();
        } else {
            std::cout << "Unable to open file for writing." << std::endl;
        }

        sf::Event event;
         while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        float currentTime = gameTime.getElapsedTime().asSeconds();
        float elapsedTime = currentTime - lastTime;

        //monster pathfollow
        if(monster.pathKinematic.size() <= 1) {
            monster.canCreateWanderPath = true;
            monster.canCreateFruitPath = true;
        }
        if(monster.pathKinematic.size() >  1) {
            float degree = atan2(monster.pathKinematic.at(monster.pathIdx)->position.y - monster.getMyKinematic()->position.y, 
                    monster.pathKinematic.at(monster.pathIdx)->position.x - monster.getMyKinematic()->position.x);\
            std::string monsterVertex = getVertexBasedOnPosition(tileGraph, monster.getMyKinematic()->position, tiles);
            std::string targetVertex = getVertexBasedOnPosition(tileGraph, monster.pathKinematic.at(monster.pathIdx)->position, tiles);
            if(monsterVertex == targetVertex && monster.pathIdx == monster.pathKinematic.size() - 1) {
                degree = monster.getMyKinematic()->orientation;
                if(!monster.canCreateWanderPath) {
                    monster.canCreateWanderPath = true;
                }
                if(!monster.canCreateFruitPath) {
                    monster.canCreateFruitPath = true;
                }
            }
            monster.pathKinematic.at(monster.pathIdx)->orientation = degree;
            float distance = sqrt(pow(monster.getMyKinematic()->position.x - monster.pathKinematic.at(monster.pathIdx)->position.x, 2) 
                            + pow(monster.getMyKinematic()->position.y - monster.pathKinematic.at(monster.pathIdx)->position.y, 2));
            if(distance <= 5.f) {
                if(monster.pathIdx != monster.pathKinematic.size() - 1) {
                    monster.pathIdx++;
                }
            }
            if(monster.pathIdx < monster.pathKinematic.size() - 1) {
                arriveBehavior->targetRadius = 5.f;
            }
            else {
                arriveBehavior->targetRadius = 0.001f;
            }
            SteeringOutput temp;
            temp.linearAcceleration = arriveBehavior->calculateAcceleration(*monster.getMyKinematic(), *monster.pathKinematic.at(monster.pathIdx)).linearAcceleration;
            temp.angularAcceleration = alignBehavior->calculateAcceleration(*monster.getMyKinematic(), *monster.pathKinematic.at(monster.pathIdx)).angularAcceleration;
            monster.update(temp, elapsedTime);
        }
        //monkeys wonder
        for(auto &monkey : monkeys) {
            
            if(monkey.canCreateWanderPath) {
                string randomVertex; 
                string monkeyVertex = getVertexBasedOnPosition(tileGraph, monkey.getMyKinematic()->position, tiles);
                while(true) {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dist(0, tiles.size() - 1);
                    int vertexId = dist(gen);
                    if(tiles.at(vertexId)->getFillColor() != sf::Color(69, 69, 69)) {
                        randomVertex = std::to_string(vertexId);
                        break;
                    }
                }
                monkey.pathIdx = 1;
                monkey.path.clear();
                monkey.pathKinematic.clear();
                monkey.path = pathFinding.searchPath(tileGraph, monkeyVertex, randomVertex);
                processPath(monkey.path, monkey, tileGraph, monkey.pathKinematic);
                
                monkey.canCreateWanderPath = false;
            }
        }
        for(auto &monkey : monkeys) {
            if(monkey.pathKinematic.size() <= 1) {
                monkey.canCreateWanderPath = true;
            }
            if(monkey.pathKinematic.size() >  1) {
                float degree = atan2(monkey.pathKinematic.at(monkey.pathIdx)->position.y - monkey.getMyKinematic()->position.y, 
                        monkey.pathKinematic.at(monkey.pathIdx)->position.x - monkey.getMyKinematic()->position.x);\
                std::string monkeyVertex = getVertexBasedOnPosition(tileGraph, monkey.getMyKinematic()->position, tiles);
                std::string targetVertex = getVertexBasedOnPosition(tileGraph, monkey.pathKinematic.at(monkey.pathIdx)->position, tiles);
                if(monkeyVertex == targetVertex && monkey.pathIdx == monkey.pathKinematic.size() - 1) {
                    degree = monkey.getMyKinematic()->orientation;
                    if(!monkey.canCreateWanderPath) {
                        monkey.canCreateWanderPath = true;
                    }
                }
                monkey.pathKinematic.at(monkey.pathIdx)->orientation = degree;
                float distance = sqrt(pow(monkey.getMyKinematic()->position.x - monkey.pathKinematic.at(monkey.pathIdx)->position.x, 2) 
                                + pow(monkey.getMyKinematic()->position.y - monkey.pathKinematic.at(monkey.pathIdx)->position.y, 2));
                if(distance <= 5.f) {
                    if(monkey.pathIdx != monkey.pathKinematic.size() - 1) {
                        monkey.pathIdx++;
                    }
                }
                if(monkey.pathIdx < monkey.pathKinematic.size() - 1) {
                    arriveBehavior->targetRadius = 5.f;
                }
                else {
                    arriveBehavior->targetRadius = 0.001f;
                }
                SteeringOutput temp;
                temp.linearAcceleration = arriveBehavior->calculateAcceleration(*monkey.getMyKinematic(), *monkey.pathKinematic.at(monkey.pathIdx)).linearAcceleration;
                temp.angularAcceleration = alignBehavior->calculateAcceleration(*monkey.getMyKinematic(), *monkey.pathKinematic.at(monkey.pathIdx)).angularAcceleration;
                monkey.update(temp, elapsedTime);
            }
        }
        for(auto &item : allItems) {
            string itemVertex = getVertexBasedOnPosition(tileGraph, item.getPosition(), tiles);
            string monsterVertex = getVertexBasedOnPosition(tileGraph, monster.getMyKinematic()->position, tiles);
            if(monsterVertex == itemVertex && monster.stamina < 4) {
                int randomNode;
                if(item.getFillColor() == sf::Color(255,0,255)) {
                    randomNode = randomInt(0, area1.size() - 1);
                    item.setPosition(area1.at(randomNode));
                }
                else if(item.getFillColor() == sf::Color(94, 91, 3)) {
                    randomNode = randomInt(0, area2.size() - 1);
                    item.setPosition(area2.at(randomNode));
                }
                else if(item.getFillColor() == sf::Color(242, 194, 194)) {
                    randomNode = randomInt(0, area3.size() - 1);
                    item.setPosition(area3.at(randomNode));
                }
                else if(item.getFillColor() == sf::Color::Green) {
                    randomNode = randomInt(0, area4.size() - 1);
                    item.setPosition(area4.at(randomNode));
                }
                monster.stamina += 5;
            }
        }
        cout << "monstert stamina: " << monster.stamina << endl;
        window.clear(sf::Color(150, 153, 146));

        for (auto tile : tiles) {
            window.draw(*tile);
        }

        for(auto &item : allItems) {
            window.draw(item);
        }

        for(auto &monkey : monkeys) {
            monkey.draw();
        }

        monster.draw();
        
        window.display();
        lastTime = currentTime;
    }
    return 0;
}