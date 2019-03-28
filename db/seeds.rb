# This file should contain all the record creation needed to seed the database with its default values.
# The data can then be loaded with the rails db:seed command (or created alongside the database with db:setup).
#
# Examples:
#
#   movies = Movie.create([{ name: 'Star Wars' }, { name: 'Lord of the Rings' }])
#   Character.create(name: 'Luke', movie: movies.first)

def create_node_values(node)
  50.times do |i|
    temperature = rand(-20..35)
    humidity = rand(0..100)

    node.values.create(temperature: temperature, humidity: humidity)
  end
end

node1 = Node.create(title: 'next to reception', device_id: 1)
create_node_values(node1)

node2 = Node.create(title: 'next to tram', device_id: 2)
create_node_values(node2)

node3 = Node.create(title: 'next to kitchen', device_id: 3)
create_node_values(node3)
