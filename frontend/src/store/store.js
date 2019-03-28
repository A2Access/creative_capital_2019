import Vue from 'vue'
import Vuex from 'vuex'
import jQuery from 'jquery'

Vue.use(Vuex)

export default new Vuex.Store({
  strict: true
  , state: {
    heatmap: null
    , nodes: []
  }
  , mutations: {
    updateNodes(state, payload) {
      state.nodes = payload
    }
  }
  , actions: {
    fetchCurrent({ commit }, payload ) {
      jQuery
        .ajax({
          type: 'POST',
          url: 'http://localhost:3000/graphql',
          contentType: 'application/json',
          dataType: 'json',
          data: { "query": "{ current { id title temperature } }" }
        })
        .done((data) => {
          commit('updateNodes', data)
        })
        .fail(() => {
          console.log('fetch failed')
          const data = [
            { id: 1, title: 'Receptionst desk', temp: 25, x: 200, y: 150, value: 15, radius: 50 }
            , { id: 2, title: 'Raccoons corner', temp: 27, x: 240, y: 250, value: 35, radius: 40 }
          ]
          commit('updateNodes', data)
        })
    }
  }
  , getters: {
    newDataPoints: (state) => {
      return state.nodes
    }
  }
})
