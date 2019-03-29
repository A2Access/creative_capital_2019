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
      const data = { "query": "{ current { id title temperature x y } }" }
      jQuery
        .ajax({
          type: 'POST',
          url: '/graphql',
          contentType: 'application/json',
          dataType: 'json',
          data: JSON.stringify(data)
        })
        .done((payload) => {
          commit('updateNodes', payload.data.current)
        })
        .fail(() => {
          console.log('fetch failed')
        })
    }
  }
  , getters: {
    newDataPoints: (state) => {
      return state.nodes.map((node) => {
        return {
          id: node.id
          , value: node.temperature
          , x: node.x
          , y: node.y
          , radius: 200
          , title: node.title
        }
      })
    }
  }
})

function random(max) {
  return Math.round(Math.random() * max)
}
