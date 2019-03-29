<template>
  <div id='map' ref="heatmap">
    <img :src="imageUrl">
    <div v-show="1 == 1">
      {{ dataPoints }}
    </div>
  </div>
</template>

<script>
 import h337 from 'heatmap.js';

 let heatmap

 export default {
   data() {
     return {
       imageUrl: window.floorPlanPath
     }
   }
   , mounted() {
     heatmap = h337.create({
       container: this.$refs.heatmap
       /* , maxOpacity: 0.85
        * , minOpacity: 0.25*/
     })

     heatmap.setData({
       max: 5,
       data: [{ x: 250, y: 250, value: 30, radius: 200 }]
     })
     setInterval(() => {
       this.$store.dispatch('fetchCurrent')
     }, 4000)
   }
   , computed: {
     dataPoints() {
       if (heatmap) {
         heatmap.setData({
           max: 35,
           data: this.$store.getters.newDataPoints
         })
       }
       return this.$store.getters.newDataPoints
     }
   }
 }
</script>

<style scoped>
 #map {
   padding: 20px;
   width: 1192px;
   height: 470px;
 }

 #map img {
   width: 100%;
 }
</style>
