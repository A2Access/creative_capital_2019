<template>
  <div id='map' ref="heatmap">
    <img src="@/assets/floor_plan.png">
    <div v-show="1 == 1">
      {{ dataPoints }}
    </div>
  </div>
</template>

<script>
 import h337 from 'heatmap.js';

 let heatmap

 export default {
   mounted() {
     heatmap = h337.create({
       container: this.$refs.heatmap
       /* , maxOpacity: 0.85
        * , minOpacity: 0.25*/
     })

     heatmap.setData({
       max: 5,
       data: [{x:200, y:150, value: 3, radius: 200}, {x:210, y:200, value: 3, radius: 150}]
     })
     setTimeout(() => {
       this.$store.dispatch('fetchCurrent')
     }, 2000)
   }
   , computed: {
     dataPoints() {
       console.log('jo')
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
   width: 100%;
 }

 #map img {
   width: 100%;
   height: 100%;
 }
 
</style>

