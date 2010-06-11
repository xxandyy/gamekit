/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Charlie C.

    Contributor(s): none yet.
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#include "gkLimitVelocityConstraint.h"
#include "gkGameObject.h"
#include "btBulletDynamicsCommon.h"




// ----------------------------------------------------------------------------
gkLimitVelocityConstraint::gkLimitVelocityConstraint() 
    :   gkConstraint(),
        m_lim(0.f, 0.f)
{
}

gkConstraint* gkLimitVelocityConstraint::clone(void)
{
    gkLimitVelocityConstraint *cl = new gkLimitVelocityConstraint(*this);
    cl->m_next = 0;
    cl->m_prev = 0;
    return cl;
}


// ----------------------------------------------------------------------------
bool gkLimitVelocityConstraint::update(gkGameObject *ob)
{
    const gkVector3 &vel = ob->getLinearVelocity();
    const gkScalar len = vel.length();

    if (m_lim.y > 0.f && len > m_lim.y)
        ob->setLinearVelocity(vel * (m_lim.y / len), TRANSFORM_LOCAL);
    else if (m_lim.x > 0.f && !gkFuzzy(len) && len < m_lim.x)
        ob->setLinearVelocity(vel * (m_lim.x / len), TRANSFORM_LOCAL);

    return false;
}
