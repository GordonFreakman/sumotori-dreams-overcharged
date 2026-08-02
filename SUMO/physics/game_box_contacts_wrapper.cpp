#include "game_runtime.h"

// FUNCTION: SUMO 0x00408c14
// FUNCTION: EDITOR 0x00408c36
void ResetGameContactLists() {
  GameBox *boxesEnd = g_gameBoxesEnd;
  GameBox *box = g_gameBoxes;
  while (box < boxesEnd) {
    box->contactLinks = NULL;
    ++box;
  }

  GameBoxJoint *joint = (GameBoxJoint *)g_gameContactObjects;
  g_gameContactLinksEnd = g_gameContactLinks;
  while ((SumoU8 *)joint < g_gameContactObjectsEnd) {
    Vector3 &unknown64 = joint->unknown64;
    Vector3 &unknownC4 = joint->unknownC4;
    Vector3 &initialImpulse = joint->initialImpulse;

    joint->limitFlags = 0;
    joint->unknown5C = 0.0f;
    joint->firstLimitImpulse = 0.0f;
    joint->secondLimitImpulse = 0.0f;
    unknown64.z = 0.0f;
    unknown64.y = 0.0f;
    unknown64.x = 0.0f;
    unknownC4.z = 0.0f;
    unknownC4.y = 0.0f;
    unknownC4.x = 0.0f;
    initialImpulse.z = 0.0f;
    initialImpulse.y = 0.0f;
    initialImpulse.x = 0.0f;

    ((GameBoxContactLink *)g_gameContactLinksEnd)->other = joint->boxes[1];
    ((GameBoxContactLink *)g_gameContactLinksEnd)->owner = joint;
    GameBoxContactLink *link = (GameBoxContactLink *)g_gameContactLinksEnd;
    GameBoxContactLink **boxContactLinks = &joint->boxes[0]->contactLinks;
    link->next = *boxContactLinks;
    *boxContactLinks = link;
    g_gameContactLinksEnd += sizeof(GameBoxContactLink);

    ((GameBoxContactLink *)g_gameContactLinksEnd)->other = joint->boxes[0];
    ((GameBoxContactLink *)g_gameContactLinksEnd)->owner = joint;
    link = (GameBoxContactLink *)g_gameContactLinksEnd;
    boxContactLinks = &joint->boxes[1]->contactLinks;
    link->next = *boxContactLinks;
    *boxContactLinks = link;
    g_gameContactLinksEnd += sizeof(GameBoxContactLink);

    ++joint;
  }
}

// FUNCTION: SUMO 0x00408dda
// FUNCTION: EDITOR 0x00408dfc
void RefreshGameContactLists() { ResetGameContactLists(); }
