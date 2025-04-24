#ifndef SCORES_H
#define SCORES_H
#include "appstate.h"
#include "player.h"

#include <vector>
#include <string>

class Scores : public AppState
{
public:
    Scores();

    Scores(std::vector<Player*> players, int level, bool game_over);

    bool finished() const;

    void draw();

    void update(Uint32 dt);

    void eventProcess(SDL_Event* ev);

    AppState* nextState();

private:

    std::vector<Player*> m_players;

    int m_level;

    bool m_game_over;

    unsigned m_score_counter;

    bool m_score_counter_run;

    unsigned m_max_score;

    Uint32 m_show_time;
};

#endif // SCORES_H
