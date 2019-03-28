<template>
  <div id="app">
    <app-map></app-map>
  </div>
</template>

<script>
import Map from './components/Map'

export default {
  name: 'App',
  components: {
    appMap: Map
  }
}
</script>

<style>
#app {
  height: 100vh;
  width: 100vw;
}
</style>
