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
      const data = { "query": "{ current { id title temperature  } }" }
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
      return state.nodes.map((node) => {
        return {
          id: node.id
          , value: node.temperature
          , x: node.id * 60
          , y: node.id * 70
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
