#pragma once

#include <Box2D/Box2D.h>

#include <iostream>

extern const int StaticType;
extern const int DynamicType;

// #1 Need to make a derived class of the b2ContactListener to get callbacks on collisions
class ContactListener : public b2ContactListener
{
   /// Called when two fixtures begin to touch.
   void BeginContact(b2Contact* contact) override
   {
      // std::cout << __func__ << std::endl;

      auto body_a = contact->GetFixtureA()->GetBody();
      auto body_b = contact->GetFixtureB()->GetBody();

      // #1
      // !! Caution: Dont delete bodies (or anything) here.  Set a flag and do it elsewhere.

      // Get the type of body A
      const auto& a_user_data = body_a->GetUserData();
      auto a_user_int_ptr = (int*)a_user_data.pointer;
      auto a_type = (a_user_int_ptr != nullptr) ? *a_user_int_ptr : StaticType;

      if (a_type == DynamicType)
         std::cout << "Detected collsion: Dynamic body: Maybe delete body A based on type" << std::endl;

      // Get the type of body A
      const auto& b_user_data = body_b->GetUserData();
      auto b_user_int_ptr = (int*)b_user_data.pointer;
      auto b_type = (b_user_int_ptr != nullptr) ? *b_user_int_ptr : StaticType;

      if (b_type == DynamicType)
         std::cout << "Detected collsion: Dynamic body: Maybe delete body B based on type" << std::endl;
   };

   /// Called when two fixtures cease to touch.
   void EndContact(b2Contact* contact) override
   {
      // std::cout << __func__ << std::endl;
   };

   /// This is called after a contact is updated. This allows you to inspect a
   /// contact before it goes to the solver.
   void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override
   {
      // std::cout << __func__ << std::endl;
      auto body_a = contact->GetFixtureA()->GetBody();
      auto body_b = contact->GetFixtureB()->GetBody();

      // Uncomment the following to make the block bounce ...
      // body_a->ApplyLinearImpulse(b2Vec2(0, -4), body_a->GetWorldCenter(), true /*wake*/);
      // body_b->ApplyLinearImpulse(b2Vec2(0, -4), body_b->GetWorldCenter(), true /*wake*/);

      // Uncomment to make the block fall through the platform
      // contact->SetEnabled(false); 
   };

   /// This lets you inspect a contact after the solver is finished. This is useful
   /// for inspecting impulses.
   void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override
   {
      // std::cout << __func__ << std::endl;
   };
};
