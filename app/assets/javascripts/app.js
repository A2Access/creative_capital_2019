webpackJsonp([1],{EjdU:function(t,e){},LABr:function(t,e){},NHnr:function(t,e,a){"use strict";Object.defineProperty(e,"__esModule",{value:!0});var n=a("7+uW"),r=a("JkCx"),i=a.n(r),s=void 0,o={data:function(){return{imageUrl:window.floorPlanPath}},mounted:function(){var t=this;(s=i.a.create({container:this.$refs.heatmap})).setData({max:5,data:[{x:200,y:150,value:3,radius:200},{x:210,y:200,value:3,radius:150}]}),setInterval(function(){t.$store.dispatch("fetchCurrent")},4e3)},computed:{dataPoints:function(){return console.log("jo"),s&&s.setData({max:35,data:this.$store.getters.newDataPoints}),this.$store.getters.newDataPoints}}},u={render:function(){var t=this.$createElement,e=this._self._c||t;return e("div",{ref:"heatmap",attrs:{id:"map"}},[e("img",{attrs:{src:this.imageUrl}}),this._v(" "),e("div",{directives:[{name:"show",rawName:"v-show",value:!0,expression:"1 == 1"}]},[this._v("\n    "+this._s(this.dataPoints)+"\n  ")])])},staticRenderFns:[]};var d={name:"App",components:{appMap:a("VU/8")(o,u,!1,function(t){a("LABr")},"data-v-64317e9a",null).exports}},c={render:function(){var t=this.$createElement,e=this._self._c||t;return e("div",{attrs:{id:"app"}},[e("app-map")],1)},staticRenderFns:[]};var p=a("VU/8")(d,c,!1,function(t){a("EjdU")},null,null).exports,l=a("mvHQ"),f=a.n(l),m=a("NYxO"),v=a("7t+N"),h=a.n(v);n.a.use(m.a);var x=new m.a.Store({strict:!0,state:{heatmap:null,nodes:[]},mutations:{updateNodes:function(t,e){t.nodes=e}},actions:{fetchCurrent:function(t,e){var a=t.commit;h.a.ajax({type:"POST",url:"/graphql",contentType:"application/json",dataType:"json",data:f()({query:"{ current { id title temperature  } }"})}).done(function(t){a("updateNodes",t.data.current)}).fail(function(){console.log("fetch failed");a("updateNodes",[{id:1,title:"Receptionst desk",temp:25,x:200,y:150,value:15,radius:50},{id:2,title:"Raccoons corner",temp:27,x:240,y:250,value:35,radius:40}])})}},getters:{newDataPoints:function(t){return t.nodes.map(function(t){return{id:t.id,value:t.temperature,x:60*t.id,y:70*t.id,radius:200,title:t.title}})}}});n.a.config.productionTip=!1,new n.a({store:x,el:"#app",components:{App:p},template:"<App/>"})}},["NHnr"]);
//# sourceMappingURL=app.js.map