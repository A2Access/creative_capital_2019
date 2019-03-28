<template>
  <div id='map' ref="heatmap">
    <img src="@/assets/floor_map.png" >
  </div>
</template>

<script>
 import h337 from 'heatmap.js';

 export default {
   created() {
     this.$store.dispatch('fetchCurrent')
   }
   , mounted() {
     const heatmap = h337.create({
       container: this.$refs.heatmap
       /* , maxOpacity: 0.85
        * , minOpacity: 0.25*/
     })

     heatmap.setData({
       max: 5,
       data: [{x:200, y:150, value: 3, radius: 200}, {x:210, y:200, value: 3, radius: 150}]
     })
   }
 }
</script>

<style scoped>
 #map {
   height: 100%;
 }
</style>

