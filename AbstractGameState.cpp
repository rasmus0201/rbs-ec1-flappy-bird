#include "AbstractGameState.h"
#include "GameEngine.h"

void AbstractGameState::ChangeState(GameEngine *game, AbstractGameState *state)
{
    game->ChangeState(state);
}