import Vue from 'vue'
import Vuex from 'vuex'
import jQuery from 'jquery'

Vue.use(Vuex)

export default new Vuex.Store({
  strict: true
  , state: {
    nodeValues: {}

  },
  mutations: {
    updateNodes() {

    }
  },
  actions: {
    fetchCurrent() {
      jQuery.post('http://localhost:3000/graphql', { "query": "{ current { id title } }" })
    }
  },
  getters: {

  }
})
