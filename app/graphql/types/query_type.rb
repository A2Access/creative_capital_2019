module Types
  class QueryType < Types::BaseObject
    field :all_nodes, [NodeType], null: false

    def all_nodes
      Node.all
    end
  end
end
