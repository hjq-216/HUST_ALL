// The Vue build version to load with the `import` command
// (runtime-only or standalone) has been set in webpack.base.conf with an alias.

// 引入一些全局样式
import './assets/css/common.css'

import Vue from 'vue'
import App from './App'
import router from './router'
import ElementUI from 'element-ui'
import 'element-ui/lib/theme-chalk/index.css'
import VueParticles from 'vue-particles'

//导入全局样式表
import './assets/css/common.css'
import qs from 'qs'
import axios from 'axios'
//配置请求的根路径
axios.defaults.baseURL = 'http://127.0.0.1:8080'
axios.interceptors.request.use(config => {
  console.log(config)
  config.headers.Authorization = window.sessionStorage.getItem('token')
  return config
}, error => {
  return Promise.reject(error)
})
Vue.prototype.$http = axios
Vue.prototype.$qs = qs
Vue.config.productionTip = false
Vue.use(ElementUI);
Vue.use(VueParticles);

/* eslint-disable no-new */
new Vue({
  el: '#app',
  router,
  components: { App },
  template: '<App/>'
})
