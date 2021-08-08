import Vue from 'vue'
import Router from 'vue-router'
import Login from '@/pages/Login.vue'
import Register from '@/pages/Register.vue'
import Create from '@/pages/Create.vue'
import Test from '@/pages/Test.vue'
import Practice from '@/pages/Practice.vue'
import Commit from '@/pages/Commit.vue'
import User from '@/pages/User.vue'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      redirect: '/login'
    },

    {
      path: '/register',
      name: 'register',
      component: Register
    },

    {
      path: '/login',
      name: 'login',
      component: Login
    },

    {
      path: '/create',
      name: 'create',
      component: Create
    },

    {
      path: '/user',
      name: 'user',
      component: User
    },

    {
      path: '/test',
      name: 'test',
      component: Test
    },

    {
      path: '/practice',
      name: 'practice',
      component: Practice
    },

    {
      path: '/commit',
      name: 'commit',
      component: Commit
    }
  ]
})
