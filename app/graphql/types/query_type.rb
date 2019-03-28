module Types
  class QueryType < Types::BaseObject
    field :current, [NodeType], null: false

    def current
      Node.all
    end
  end
end
