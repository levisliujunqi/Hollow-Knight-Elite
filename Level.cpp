// level.cpp
#include "Level.h"
#include <QGraphicsItem>

Level::Level(UIController* uicontroller, int id, bool readuser, QObject* parent)
    : QObject(parent), m_uiController(uicontroller), m_levelId(id),visitelements(false)
{
    checkifontheground=[&](Character *cha){
        for(auto &p:m_grounds){
            if(m_uiController->IsCrash(cha->item,p->item)) return true;
        }
        return false;
    };
    //m_uiController->SetBackgroundColor(Qt::white);
    m_uiController->SetBackgroundPicture(QPixmap(":/res/playscenebackground.png"));
    QPixmap qpixmap(":/res/Player/Still/1/0.png");
    SqliteDB db(m_uiController->getnowdir()+"/database.sqlite");
    if(!readuser){
        vector<string> columns={"health","ad","movev","fastmovev","jumpv","attackdelay","fastmovedelay","attackpretime","x","y","width","height","addbloodcd","preattack","prefastmove","preaddblood","maxhealth"};
        auto result=db.query("select * from origin where levelid="+to_string(id)+" and class='Player';",columns);
        //m_player = new Player(m_uiController, 100,3,5,8,6.5,500,1000,1,500, 500,30,50,3000,qpixmap,checkifontheground);
        m_player=new Player(m_uiController,stod(result[0][16]),stod(result[0][0]),stod(result[0][1]),stod(result[0][2]),stod(result[0][3]),stod(result[0][4]),stoi(result[0][5]),
                              stoi(result[0][6]),stoi(result[0][7]),stod(result[0][8]),stod(result[0][9]),stod(result[0][10]),stod(result[0][11]),stoi(result[0][12]),stoi(result[0][13]),stoi(result[0][14]),stoi(result[0][15]),qpixmap,checkifontheground);
        m_characters.append(m_player);
        m_player->busystate[Character::DROP]=new busystateinfo(0);
    }else{
        vector<string> columns={"health","ad","movev","fastmovev","jumpv","attackdelay","fastmovedelay","attackpretime","x","y","width","height","addbloodcd","preattack","prefastmove","preaddblood","maxhealth"};
        auto result=db.query("select * from user where levelid="+to_string(id)+" and class='Player';",columns);
        //m_player = new Player(m_uiController, 100,3,5,8,6.5,500,1000,1,500, 500,30,50,3000,qpixmap,checkifontheground);
        m_player=new Player(m_uiController,stod(result[0][16]),stod(result[0][0]),stod(result[0][1]),stod(result[0][2]),stod(result[0][3]),stod(result[0][4]),stoi(result[0][5]),
                              stoi(result[0][6]),stoi(result[0][7]),stod(result[0][8]),stod(result[0][9]),stod(result[0][10]),stod(result[0][11]),stoi(result[0][12]),stoi(result[0][13]),stoi(result[0][14]),stoi(result[0][15]),qpixmap,checkifontheground);
        m_characters.append(m_player);
        m_player->busystate[Character::DROP]=new busystateinfo(0);
    }
    createLevelElements();
    createEnemies(readuser,db);
    creategates();
    m_elements.push_back(new PlayerInfo(uicontroller,m_player));
    render=new QTimer(this);
    render->start(16);
    setupConnections();
    connect(render,&QTimer::timeout,this,&Level::renderfunc);
}

Level::~Level(){
    if(m_player!=nullptr) delete m_player;
    for(auto p:m_enemies) delete p;
}
void Level::InitializeLevel()
{
    m_uiController->clear();
    m_uiController->SetBackgroundColor(Qt::white);
}

void Level::setupConnections()
{

    connect(m_uiController->keypresseater,&KeyPressEater::KeyPress,m_player,&Player::keypress);
    connect(m_uiController->keypresseater,&KeyPressEater::KeyReelase,m_player,&Player::keyrelease);
    connect(m_player,&Player::addelements,this,&Level::addelementsslot);

    for(auto p:m_enemies){
        connect(m_player,&Character::attacksignal,p,&Character::attackslots);
        connect(p,&Character::attacksignal,m_player,&Character::attackslots);
        connect(p,&Enemy::addelements,this,&Level::addelementsslot);
    }
}

void Level::createLevelElements()
{

    switch (m_levelId) {
        case 1:
            m_grounds.push_back(new Grounds(m_uiController->CreateRect(0, 200, 1000, 20, Qt::gray)));
            m_grounds.push_back(new Grounds(m_uiController->CreateRect(0, 400, 1000, 20, Qt::gray)));
            m_grounds.push_back(new Grounds(m_uiController->CreateRect(0, 580, 1000, 20, Qt::gray)));
            break;
        case 2:
            m_grounds.push_back(new Grounds(m_uiController->CreateRect(0, 200, 1000, 20, Qt::gray)));
            m_grounds.push_back(new Grounds(m_uiController->CreateRect(0, 400, 1000, 20, Qt::darkGray)));
            m_grounds.push_back(new Grounds(m_uiController->CreateRect(0, 580, 1000, 20, Qt::darkGray)));
            break;
    }
}

void Level::createEnemies(bool readuser,SqliteDB &db)
{
    QPixmap qpixmap(":/res/Enemy1/walk/1/0.png");
    vector<string> columns={"health","ad","movev","fastmovev","jumpv","attackdelay","fastmovedelay","attackpretime","x","y","width","height","addbloodcd","preattack","prefastmove","preaddblood","maxhealth"};
    if(!readuser){
        auto result1=db.query("select * from origin where levelid="+to_string(m_levelId)+" and class='Enemy1';",columns);
        for(auto result:result1){
            m_enemies.append(new Enemy1(m_uiController, stod(result[16]),stod(result[0]),stod(result[1]),stod(result[2]),stod(result[3]),stod(result[4]),stoi(result[5]),
                                        stoi(result[6]),stoi(result[7]),stod(result[8]),stod(result[9]),stod(result[10]),stod(result[11]),stoi(result[12]),stoi(result[13]),stoi(result[14]),stoi(result[15]),qpixmap,checkifontheground));
        }
        auto result2=db.query("select * from origin where levelid="+to_string(m_levelId)+" and class='Boss';",columns);
        for(auto result:result2){
            m_enemies.append(new Boss(m_uiController, stod(result[16]),stod(result[0]),stod(result[1]),stod(result[2]),stod(result[3]),stod(result[4]),stoi(result[5]),
                                        stoi(result[6]),stoi(result[7]),stod(result[8]),stod(result[9]),stod(result[10]),stod(result[11]),stoi(result[12]),stoi(result[13]),stoi(result[14]),stoi(result[15]),qpixmap,checkifontheground));
        }
    }else{
        auto result1=db.query("select * from user where levelid="+to_string(m_levelId)+" and class='Enemy1';",columns);
        for(auto result:result1){
            m_enemies.append(new Enemy1(m_uiController, stod(result[16]),stod(result[0]),stod(result[1]),stod(result[2]),stod(result[3]),stod(result[4]),stoi(result[5]),
                                        stoi(result[6]),stoi(result[7]),stod(result[8]),stod(result[9]),stod(result[10]),stod(result[11]),stoi(result[12]),stoi(result[13]),stoi(result[14]),stoi(result[15]),qpixmap,checkifontheground));
        }
        auto result2=db.query("select * from user where levelid="+to_string(m_levelId)+" and class='Boss';",columns);
        for(auto result:result2){
            m_enemies.append(new Boss(m_uiController, stod(result[16]),stod(result[0]),stod(result[1]),stod(result[2]),stod(result[3]),stod(result[4]),stoi(result[5]),
                                      stoi(result[6]),stoi(result[7]),stod(result[8]),stod(result[9]),stod(result[10]),stod(result[11]),stoi(result[12]),stoi(result[13]),stoi(result[14]),stoi(result[15]),qpixmap,checkifontheground));
        }
    }
    db.excusesql(QString::fromStdString("DELETE FROM user where levelid="+to_string(m_levelId)+";"));
    for(auto p:m_enemies){
        m_characters.append(p);
        p->busystate[Character::DROP]=new busystateinfo(0);
    }
}

void Level::creategates()
{
    QPixmap up(":/res/Gate/up.jpg");
    QPixmap down(":/res/Gate/down.jpg");
    switch(m_levelId){
        case 1:
            m_gate.append(new Gate(m_uiController,10,490,130,130,{300,300},up));
            m_gate.append(new Gate(m_uiController,20,300,130,130,{500,500},down));
            m_gate.append(new Gate(m_uiController,830,300,130,130,{300,100},up));
            m_gate.append(new Gate(m_uiController,820,100,130,130,{300,300},down));
            break;
        case 2:
            m_gate.append(new Gate(m_uiController,10,490,130,130,{300,300},up));
            m_gate.append(new Gate(m_uiController,20,300,130,130,{500,500},down));
            m_gate.append(new Gate(m_uiController,830,300,130,130,{300,100},up));
            m_gate.append(new Gate(m_uiController,820,100,130,130,{300,300},down));
            break;
        default:
            break;
    }
}


void Level::renderfunc()
{
    for(auto it=m_characters.begin();it!=m_characters.end();){
        if((*it)->isdead()){
            bool flag=0;
            if(auto p=dynamic_cast<Player*>(*it)) flag=1;
            if(!flag) m_enemies.removeAll(*it);
            delete *it;
            it=m_characters.erase(it);
            if(flag){
                m_player=nullptr;
                emit levelfail();
                render->stop();
                return;
            }
        }else{
            auto busystate_=(*it)->busystate;
            if(busystate_.empty()){
                (*it)->showstillpicture();
            }else{
                for(auto [p,q]:busystate_){
                    switch(p){
                        case Character::MOVEL:
                            (*it)->moveleft();
                            break;
                        case Character::MOVER:
                            (*it)->moveright();
                            break;
                        case Character::JUMP:
                            (*it)->jump();
                            break;
                        case Character::ATTACK:
                            (*it)->attack();
                            break;
                        case Character::DROP:
                            (*it)->drop();
                            break;
                        case Character::FASTMOVE:
                            (*it)->fastmove();
                            break;
                        default:
                            break;
                    }
                }
            }
            it++;
        }
    }
    if(m_enemies.isEmpty()){
        emit levelCompleted();
    }
    for (Enemy* enemy:m_enemies) {
        if (!enemy->isdead())
            enemy->AI(m_player);
    }

    while(visitelements);
    visitelements=true;
    for(auto it=m_elements.begin();it!=m_elements.end();){
        bool result=(*it)->showpicture();
        if(!result){
            delete *it;
            it=m_elements.erase(it);
        }else{
            it++;
        }
    }
    visitelements=false;

    for(auto p:m_gate){
        if(m_uiController->IsCrash(p->item,m_player->item)){
            m_player->busystate.clear();
            m_player->walk(p->to.first,p->to.second);
            m_player->adddropstate();
        }
    }
}

void Level::addelementsslot(Elements *ele)
{
    while(visitelements);
    visitelements=true;
    m_elements.push_back(ele);
    visitelements=false;
}

void Level::closeevent()
{
    int reply=QMessageBox::question(nullptr,"询问","是否要存档？",QMessageBox::Yes|QMessageBox::No);
    if(reply==QMessageBox::Yes){
        saveToDatabase();
    }
}


void Level::saveToDatabase() {
    SqliteDB db(m_uiController->getnowdir()+"/database.sqlite");
    db.excusesql(QString::fromStdString("DELETE FROM user where levelid="+to_string(m_levelId)+";"));

    // 保存player数据
    if (m_player) {
        QString playerSql = QString("INSERT INTO user (class,health,ad,movev,fastmovev,jumpv,attackdelay,fastmovedelay,attackpretime,x,y,width,height,addbloodcd,preattack,prefastmove,preaddblood,levelid,maxhealth) VALUES('Player',%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18);")
                                .arg(m_player->health)
                                .arg(m_player->ad)
                                .arg(m_player->movev)
                                .arg(m_player->fastmovev)
                                .arg(m_player->jumpv)
                                .arg(m_player->attackdelay)
                                .arg(m_player->fastmovedelay)
                                .arg(m_player->attackpretime)
                                .arg(m_player->x)
                                .arg(m_player->y)
                                .arg(m_player->width)
                                .arg(m_player->height)
                                .arg(m_player->addbloodcd)
                                .arg(m_player->preattack)
                                .arg(m_player->prefastmove)
                                .arg(m_player->preaddblood)
                                .arg(m_levelId)
                                .arg(m_player->maxhealth);
        db.excusesql(playerSql);
    } else {
        qWarning() << "保存 player 数据失败";
    }

    // 保存enemies数据
    for (Enemy* enemy : m_enemies) {
        if (!enemy) continue;
        QString enemySql="";
        if(auto it=static_cast<Enemy1*>(enemy)){
            enemySql = QString("INSERT INTO user (class,health,ad,movev,fastmovev,jumpv,attackdelay,fastmovedelay,attackpretime,x,y,width,height,addbloodcd,preattack,prefastmove,preaddblood,levelid,maxhealth) VALUES('Enemy1',%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18);")
                                .arg(it->health)
                                .arg(it->ad)
                                .arg(it->movev)
                                .arg(it->fastmovev)
                                .arg(it->jumpv)
                                .arg(it->attackdelay)
                                .arg(it->fastmovedelay)
                                .arg(it->attackpretime)
                                .arg(it->x)
                                .arg(it->y)
                                .arg(it->width)
                                .arg(it->height)
                                .arg(it->addbloodcd)
                                .arg(it->preattack)
                                .arg(it->prefastmove)
                                .arg(it->preaddblood)
                                .arg(m_levelId)
                                .arg(it->maxhealth);
        }else{
            auto it1=static_cast<Boss*>(enemy);
            enemySql = QString("INSERT INTO user (class,health,ad,movev,fastmovev,jumpv,attackdelay,fastmovedelay,attackpretime,x,y,width,height,addbloodcd,preattack,prefastmove,preaddblood,levelid,maxhealth) VALUES('Boss',%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18);")
                .arg(it1->health)
                .arg(it1->ad)
                .arg(it1->movev)
                .arg(it1->fastmovev)
                .arg(it1->jumpv)
                .arg(it1->attackdelay)
                .arg(it1->fastmovedelay)
                .arg(it1->attackpretime)
                .arg(it1->x)
                .arg(it1->y)
                .arg(it1->width)
                .arg(it1->height)
                .arg(it1->addbloodcd)
                .arg(it1->preattack)
                .arg(it1->prefastmove)
                .arg(it1->preaddblood)
                .arg(m_levelId)
                .arg(it1->maxhealth);
        }
        db.excusesql(enemySql);
    }

    qDebug() << "数据保存完成";
}

