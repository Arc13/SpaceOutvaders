/**
 * @file transition_engine.cpp
 * @brief Un moteur pour le système de transition
 * @author SOLLIER Alexandre
 * @version 1.1
 * @date 10 janvier 2020
 */

#include "transition_engine.h"

#define TRANSITIONENGINE nsTransition::TransitionEngine

void TRANSITIONENGINE::update(const std::chrono::microseconds &delta)
{
    // Update every transitioned items
    TransitionVector_t::iterator iter = m_transitionList.begin();
    while (iter != m_transitionList.end())
    {
        // Check if the item is finished, and remove it from the list in that case
        if (iter->isFinished())
        {
            m_transitionList.erase(iter++);
        }
        else
        {
            iter->addToElapsed(delta);
            ++iter;
        }
    }
} // update()

void TRANSITIONENGINE::startContract(const TransitionContract &contract)
{
    m_transitionList.push_back(Transition(contract));
} // startContract()

void TRANSITIONENGINE::finishEveryTransition(const Transition::TransitionFinishModes &finishMode)
{
    // Mark every transition as finished
    for (Transition &transition : m_transitionList)
    {
        transition.finish(finishMode);
    }
} // finishEveryTransition()

void TRANSITIONENGINE::finishEveryTransitionOfTarget(const ITransitionable &transitionable, const Transition::TransitionFinishModes &finishMode)
{
    for (Transition &transition : m_transitionList)
    {
        // Check if the address of the target is the same one as the address of transitionable
        if (&(transition.getTarget()) == &transitionable)
        {
            transition.finish(finishMode);
        }
    }
}  // finishEveryTransitionOfTarget()

#undef TRANSITIONENGINE
